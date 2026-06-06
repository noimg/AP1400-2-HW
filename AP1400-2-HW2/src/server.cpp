#include "server.h"

std::vector<std::string> pending_trxs;

using MPD = std::map<std::shared_ptr<Client>, double>;
void show_wallets(const Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: *((MPD*)&server))
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

Server::Server() {}

std::shared_ptr<Client> Server::add_client(std::string id)
{
	std::default_random_engine e;
	std::uniform_int_distribution u(0, 9);
	std::string tail = "";
	for (int i = 0; i < 4; ++i)
		tail += std::to_string(u(e));

	for (const auto& c : clients)
    {
		if (c.first->get_id() == id)
			id += tail;
	}
	auto cli = std::make_shared<Client>(id, *this);
	clients[cli] = 5.0;
	return cli;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto& c : clients)
        if (c.first->get_id() == id)
            return c.first;
    return nullptr;
}

double Server::get_wallet(std::string id) const
{
    for (const auto& c : clients)
        if (c.first->get_id() == id)
            return c.second;
    return 0.0;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::regex pattern("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
    std::smatch results;
    if (!std::regex_match(trx, results, pattern))
        throw std::runtime_error("the trx string is not standard");
    
    sender = results[1];
    receiver = results[2];
    value = std::stod(results[3]);
    
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender, receiver;
    double value;

    if(!parse_trx(trx, sender, receiver, value))
        return false;

    auto recevier_ptr = get_client(receiver);
	auto sender_ptr = get_client(sender);

    if(recevier_ptr == nullptr || sender_ptr == nullptr)
        return false;
    
    bool authentic = crypto::verifySignature(sender_ptr->get_publickey(), trx, signature);
    if(authentic && (value <= sender_ptr->get_wallet()))
    {
        pending_trxs.push_back(trx);
        return true;
    }

    return false;
}

size_t Server::mine()
{
    std::string mempool{};
    for(const auto& trx : pending_trxs)
        mempool += trx;

    bool success = false;
    size_t nonce = 0;
    while (!success)
    {
        for (auto& [client_ptr, value] : clients)
        {
            nonce = client_ptr->generate_nonce();
            std::string final_string = mempool + std::to_string(nonce);
            std::string hash{crypto::sha256(final_string)};
            if (hash.substr(0, 10).find("000") != std::string::npos)
            {
                success = true;
                value += 6.25;
                break;
            }
        }
    }

    for (const auto& trx : pending_trxs)
    {
        std::string sender, receiver;
        double value;
        parse_trx(trx, sender, receiver, value);

        clients[get_client(sender)] -= value;
        clients[get_client(receiver)] += value;
    }
    pending_trxs.clear();
    return nonce;
}
def adjacentElementsProduct(inputArray):
    return max([inputArray[i]*inputArray[i + 1] for i in range(len(inputArray) - 1)])

def allLongestStrings(inputArray):
    return [s for s in inputArray if len(s) == max(map(len, inputArray))]

def checkPalindrome(inputString):
    return inputString == inputString[::-1]

def commonCharacterCount(s1, s2):
    return sum(min(s1.count(c), s2.count(c)) for c in set(s1))

def areSimilar(A, B):
    return sorted(A) == sorted(B) and sum(a != b for a, b in zip(A, B)) <= 2

def palindromeRearranging(inputString):
    return sum(inputString.count(c) % 2 for c in set(inputString)) <= 1

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [substitutionElem if x == elemToReplace else x for x in inputArray]

def evenDigitsOnly(n):
    return all(int(i) % 2 == 0 for i in str(n))

def alphabeticShift(inputString):
    return "".join(chr((ord(i) + 1 - ord('a')) % 26 + ord('a')) for i in inputString)

def firstDigit(inputString):
    return int(next(c for c in inputString if c.isdigit()))
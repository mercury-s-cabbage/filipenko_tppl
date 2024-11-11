def prefix(s):
    result = ""
    digits = []
    signs = []
    if not s:
       raise SyntaxError("Empty string")
    s = s.split(' ')
    for a in s:
        if a in ["+", "-", "/", "*"]:
            signs.append(a)
        elif a.isdigit():
            digits.append(a)
        else:
            raise SyntaxError("Incorrect string: use only sings, digits and spaces")

    if len(digits) - len(signs) != 1:
        raise SyntaxError("Incorrect string: you should type N digits ans N-1 signs")
    for i in range(len(signs)):
        result+=digits[i] + ' '
        result+=signs[i]
        result+=' '
    result += digits[-1]
    return result


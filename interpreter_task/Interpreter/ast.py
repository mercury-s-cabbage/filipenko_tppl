#ast.py
from .token import Token

class Node:
    pass

class Number(Node):

    def __init__(self, token: Token):
        self.token = token

    def __str__(self):
        return f"{self.__class__.__name__} ({self.token})"

class BinOp(Node):
    def __init__(self, left: Node, op: Token, right: Node):
        self.left = left
        self.op = op
        self.right = right

    def __str__(self):
        return f"{self.__class__.__name__}" +\
            f"{self.op.value}({self.left}, {self.right})"

class UnaryOp(Node):
    def __init__(self, op: Token, expr: Node):
        self.op = op
        self.expr = expr

    def __str__(self):
        return f"{self.__class__.__name__}{self.op.value}({self.expr}"
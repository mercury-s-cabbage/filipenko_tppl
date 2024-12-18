from .parser import Parser
from .ast import Number, BinOp, UnaryOp

class NoneVisitor:
    def visit(self):
        pass

class Interpreter(NoneVisitor):
    def __init__(self):
        self._parser = Parser()

    def visit(self, node):
        if isinstance(node, Number):
            return self._visit_number(node)
        elif isinstance(node, BinOp):
            return self._visit_binop(node)
        elif isinstance(node, UnaryOp):
            return self._visit_unary(node)

    def _visit_unary(self, node):
        match node.op.value:
            case "+":
                return +self.visit(node.expr)
            case "-":
                return -self.visit(node.expr)
            case "_":
                raise RuntimeError("Bad Unaryop")


    def _visit_number(self, node: Number) -> float:
        return float(node.token.value)

    def _visit_binop(self, node: BinOp):
        match node.op.value:
            case "+":
                return self.visit(node.left) + self.visit(node.right)
            case "-":
                return self.visit(node.left) - self.visit(node.right)
            case "/":
                return self.visit(node.left) / self.visit(node.right)
            case "*":
                return self.visit(node.left) * self.visit(node.right)
    def eval(self, code:str) -> float:
        tree = self._parser.eval(code)
        return self.visit(tree)


import pytest
from interpreter_task.Interpreter.interpreter import Interpreter

# scope="function" - create new interpreter_task for each function
@pytest.fixture(scope="function")
def interpreter():
    return Interpreter()

class TestInterpreter:

    def test_add(self, interpreter):
        assert interpreter.eval("2+2") == 4
        assert interpreter.eval("2+3") == 5
    def test_sup(self, interpreter):
        assert interpreter.eval("2-2") == 0
        assert interpreter.eval("3-2") == 1
    def test_spaces(self, interpreter): #добавили тесты для пробелов
        assert interpreter.eval("  2   +   2  ") == 4
    def test_big(self, interpreter): #добавили тесты для больших чисел
        assert interpreter.eval("222+34522") == 34744

    def test_term(self, interpreter):
        assert interpreter.eval("2+3-1") == 4
        assert interpreter.eval("2+2-4+3") == 3

    def test_term1(self, interpreter):
        assert interpreter.eval("2*3") == 6
        assert interpreter.eval("2*3/6") == 1

    def test_parens(self, interpreter):
        assert interpreter.eval("(2+2)*2") == 8
        assert interpreter.eval("(3-3)") == 0
        assert interpreter.eval("(3+3+3)/(1+8)") == 1
        assert interpreter.eval("(((3)))") == 3
        assert interpreter.eval("(3-(3+1))") == -1

    def test_unary(self, interpreter):
        assert interpreter.eval("----++2") == 2
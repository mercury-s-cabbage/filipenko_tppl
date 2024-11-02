import pytest
from PycharmProjects.filipenko_tppl.prefix.Interpreter import Interpreter

# scope="function" - create new interpreter for each function
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
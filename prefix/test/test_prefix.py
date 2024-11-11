import pytest
from prefix.main import prefix
def test_simple():
    assert prefix("+ 1 1") == "1 + 1"
    assert prefix("- 1 1") == "1 - 1"
    assert prefix("* 1 1") == "1 * 1"
    assert prefix("/ 1 1") == "1 / 1"

def test_complete():
    assert prefix("+ * 30 - 4 6 7") == "30 + 4 * 6 - 7"
    assert prefix("3 + 4 6 7 * -") == "3 + 4 * 6 - 7"

def test_value_error_message():
    with pytest.raises(SyntaxError, match="Empty string"):
        prefix("")

    with pytest.raises(SyntaxError, match="Incorrect string: you should type N digits ans N-1 signs"):
        prefix("* - / 7")

    with pytest.raises(Exception, match="Incorrect string: you should type N digits ans N-1 signs"):
        prefix("* 6 7 2")

    with pytest.raises(Exception, match="Incorrect string: use only sings, digits and spaces"):
        prefix("ghm")

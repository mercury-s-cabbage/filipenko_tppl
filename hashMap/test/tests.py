import pytest
from ExtDict import ExtDict


class TestExtDict:
    def setup_method(self):
        self.map = ExtDict()
        self.map["value1"] = 6
        self.map["value2"] = 6
        self.map["1"] = 0
        self.map["2"] = 3
        self.map["1, 5"] = 1
        self.map["5, 5"] = 5
        self.map["10, 5"] = 5
        self.map["(2, 3)"] = 200
        self.map["(3, 4)"] = 300

    def test_getitem(self):
        assert self.map["value1"] == 6
        assert self.map["1"] == 0

        with pytest.raises(KeyError):
            self.map["non_existent_key"]

    def test_iloc(self):
        assert self.map.iloc[0] == 200
        assert self.map.iloc[1] == 300
        assert self.map.iloc[2] == 0

        with pytest.raises(ValueError):
            self.map.iloc["invalid"]

        with pytest.raises(IndexError):
            self.map.iloc[100]

    def test_get_condition(self):
        ploc = self.map.ploc

        condition = ploc._get_condition(">=10")
        assert condition == (">=", 10)

        condition = ploc._get_condition("<5")
        assert condition == ("<", 5)

        ploc = self.map.ploc

        with pytest.raises(SyntaxError):
            ploc._get_condition("invald_condition")

        with pytest.raises(SyntaxError):
            ploc._get_condition("=4=5")

        with pytest.raises(SyntaxError):
            ploc._get_condition(">&")

    def test_extract_int_keys(self):
        result = self.map.ploc._extract_int_keys()
        assert result == [
            (1,), (2,), (1, 5), (5, 5), (10, 5), (2, 3), (3, 4)
        ]

    def test_extract_int_keys_empty(self):
        empty_map = ExtDict()
        result = empty_map.ploc._extract_int_keys()
        assert result == []

    def test_extract_by_condition(self):
        ploc = self.map.ploc

        result = ploc._extract_by_condition([(">=", 1)])
        expected = {(1,): 0, (2,): 3}
        assert result == expected

        result = ploc._extract_by_condition([("<", 3)])
        expected = {(1,): 0, (2,): 3}
        assert result == expected

        ploc = self.map.ploc

        with pytest.raises(KeyError):
            ploc._extract_by_condition("invalid_condition")

    def test_ploc_single_condition(self):
        result = self.map.ploc["<>2"]
        expected = {(1,): 0}
        assert result == expected

        result = self.map.ploc["=2"]
        expected = {(2,): 3}
        assert result == expected

    def test_ploc_multiple_conditions(self):
        result = self.map.ploc[">2, <=5"]
        expected = {(3, 4): 300, (5, 5): 5, (10, 5): 5}
        assert result == expected

    def test_ploc_invalid_input(self):
        with pytest.raises(KeyError):
            self.map.ploc[123]


    def test_general_dict_methods(self):
        self.map["3, 6"] = 42
        assert self.map["3, 6"] == 42

        del self.map["value1"]
        assert "value1" not in self.map

        self.map["value2"] = 10
        assert self.map["value2"] == 10

        keys = list(self.map.keys())
        values = list(self.map.values())
        assert len(keys) == len(values)

    def test_invalid_keys(self):
        with pytest.raises(KeyError):
            self.map["nonexistent_key"]
import ast
from xml.etree.ElementTree import tostring


class ExtDict(dict):
    def __getitem__(self, key):
        if key in self:
            return super().__getitem__(key)
        raise KeyError(key)

    @property
    def iloc(self):
        class ILocWrapper:
            def __init__(self, parent):
                self.parent = parent

            def __getitem__(self, index):
                if isinstance(index, int):
                    return list(sorted(self.parent.items(), key=lambda item: item[0]))[index][1]
                else:
                    raise ValueError("Index must be integer")

        return ILocWrapper(self)


    @property
    def ploc(self):
        class PlocWrapper:
            def __init__(self, parent):
                self.conditions = [">", ">=", "<", "<=", "=", "<>"]
                self.parent = parent

            # extract (sign,value) from input condition
            def _get_condition(self, line: str):
                sign = ""
                value = ""

                for i in line:
                    if i in self.conditions and not(value):
                        sign += i
                    elif i in self.conditions and value:
                        raise SyntaxError("Conditional error")
                    else:
                        value += i

                if not(value) or not(sign):
                    raise SyntaxError("Conditional error")

                if value.isnumeric() and sign in self.conditions:
                     value = int(value)
                else:
                    raise SyntaxError("Conditional error")
                return (sign, value)


            # extract keys that can be converted to int
            def _extract_int_keys(self):
                result = []
                for key in self.parent.keys():
                    try:
                        parsed_key = ast.literal_eval(key)

                        if isinstance(parsed_key, int):
                            result.append((parsed_key,))
                        elif isinstance(parsed_key, tuple) and all(isinstance(x, int) for x in parsed_key):
                            result.append(parsed_key)
                    except (ValueError, SyntaxError):
                        continue
                return result


            # extract all elements with key corresponding to conditions
            def _extract_by_condition(self, conditions):
                try:
                    elements = {}
                    conditions_number = len(conditions)
                    keys = [key for key in self._extract_int_keys() if len(key) == conditions_number]

                    for i, (sign, value) in enumerate(conditions):
                        if sign == "<":
                            keys = [key for key in keys if  key[i] < value]
                        elif sign == "<=":
                            keys = [key for key in keys if  key[i] <= value]
                        elif sign == ">":
                            keys = [key for key in keys if  key[i] > value]
                        elif sign == ">=":
                            keys = [key for key in keys if  key[i] >= value]
                        elif sign == "=":
                            keys = [key for key in keys if  key[i] == value]
                        elif sign == "<>":
                            keys = [key for key in keys if  key[i] != value]

                    for key in keys:
                        if f'{key}' in self.parent.keys():
                            elements[key] = self.parent[f'{key}']
                        if ', '.join(map(str, key)) in self.parent.keys():
                            elements[key] = self.parent[', '.join(map(str, key))]
                    return elements
                except:
                    raise KeyError(f"Sign not in keys")


            def __getitem__(self, input_condition):
                if isinstance(input_condition, str):
                    conditions = []
                    for part in input_condition.split(","):
                        conditions.append(self._get_condition("".join(part.split())))

                    return self._extract_by_condition(conditions)
                raise KeyError(f"Condition must be string")

        return PlocWrapper(self)
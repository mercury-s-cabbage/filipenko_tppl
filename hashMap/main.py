from ExtDict import ExtDict

# Пример использования
map = ExtDict()

map["value1"] = 1
map["value2"] = 2
map["value3"] = 3
map["1"] = 10
map["2"] = 20
map["3"] = 30
map["1, 5"] = 100
map["5, 5"] = 200
map["10, 5"] = 300

print(map.iloc[0])
print(map.iloc[2])
print(map.iloc[5])
print(map.iloc[8])

map = ExtDict()
map["value1"] = 1
map["value2"] = 2
map["value3"] = 3
map["1"] = 10
map["2"] = 20
map["3"] = 30
map["(1, 5)"] = 100
map["(5, 5)"] = 200
map["(10, 5)"] = 300
map["(1, 5, 3)"] = 400
map["(5, 5, 4)"] = 500
map["(10, 5, 5)"] = 600

print(map.ploc[">=1"])
print(map.ploc["<3"])
print(map.ploc[">0, >0"])
print(map.ploc[">=10, >0"])
print(map.ploc["<5, >=5, >=3"])

--Declare a table using syntactic sugar
local table = {
    foo= 45,
    tab = {
        x = 23
    },
    place = 10
}

--Declare an example member-like function
function table:func(y)
    print(self.tab.x + y)
end

print(table.place) 			  --prints out 10
print(table["place"])         --prints out 10

print(table.tab.x) 			  --prints out 23
print(table["tab"]["x"])      --prints out 23
print(table.tab["x"])         --prints out 23

table.func(table, 175)        --prints out 198
table:func(150)			      --prints out 173
print(table.func)             --prints out function: address
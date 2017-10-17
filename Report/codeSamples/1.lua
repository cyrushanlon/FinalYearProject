--Inline declaration of a table
local tab1 = {
    foo= 45,
    tab = {
        x = 23
    },
    place = 10
}

--Declaration of an example member-like function
function tab1:func(y)
    print(self.tab.x + y)
end

tab1:func(25)

function tab1.func(self, y)
    print(self.tab.x + y)
end

tab1.func(tab1, 25)

print(tab1.place) 			 --prints out 10
print(tab1["place"])         --prints out 10
print(tab1.tab["x"])         --prints out 23
--Inline declaration of a table
local tab = {
    foo= 45,
    tab = {
        x = 23
    },
    place = 10
}

--Declaration of an example member-like function
function tab:func(y)
    print(self.tab.x + y)
end

tab:func(25)

function tab.func(self, y)
    print(self.tab.x + y)
end

tab1.func(tab, 25)

print(tab.place) 			 --prints out 10
print(tab["place"])         --prints out 10
print(tab.tab["x"])         --prints out 23

--declaration of a table using numerical indices
local array = {
    "this is a string",
    105,
    function(x) print("this is a function"..x) end
} 

print(array[1])             --prints out this is a string
print(array[2])             --prints out 105
array[3]("!")               --prints out this is a function!

local tab = {
    foo = "this is a string",
    105,
    "this is another string",
    [333] = function(x) print("this is a function"..x) end
}

for k,v in pairs(tab) do 
    print(k, v) 
end
--[[ prints out the following:
1	105
2	this is another string
333	function: 0x1663b90
foo	this is a string
]]

for k,v in ipairs(tab) do 
    print(k, v) 
end
--[[ prints out the following:
1	105
2	this is another string
]]
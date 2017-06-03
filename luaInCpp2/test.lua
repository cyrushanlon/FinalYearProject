logout("one argument")
logout("hello", "this", "is", "many", "args", "with", "a", "number:", 1 )

function add ( x, y )
    print("from lua: "..x .." + "..y.." = "..x+y)
	return x + y
end


local dog = Dog("Spot")
print("from lua: the dogs name is ".. dog:getName())
print(dog:talk("bark!"))

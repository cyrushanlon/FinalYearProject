local settings = {
    gridSize = 15,
    scale = 32,
    startlen = 6,
    updateTime = 0.1
}

--containers
local snake = {}
local food = {}
local border = {}

--globals
local direction = 3
local moveTime = 0

function createObject(tab, tex)
    local piece = {}

    piece.drawable = DrawableComponent.New()
    piece.drawable:SetTexture(tex)
    piece.drawable:SetPos(-settings.scale, -settings.scale)

    piece.entity = Entity.New("piece" .. #tab)
    piece.entity:AddDrawable(piece.drawable)

    piece.gridpos = {x = -1, y = -1}
    piece.oldgridpos = {x = -1, y = -1}

    table.insert(tab, piece)
    
    return #tab --return the location of the piece
end

function moveObject(tab, index, x, y)
    local piece = tab[index]
    piece.drawable:SetPos(x * settings.scale, y * settings.scale)
    
    piece.oldgridpos.x = piece.gridpos.x
    piece.oldgridpos.y = piece.gridpos.y

    piece.gridpos.x = x
    piece.gridpos.y = y
end

function Init()
    --create border
    for i = 0, (settings.gridSize + 1) do --top and bottom
        createObject(border, "resources/textures/snakeborder.png")
        moveObject(border, #border, i, 0)
        createObject(border, "resources/textures/snakeborder.png")
        moveObject(border, #border, i, (settings.gridSize + 1))
    end
    for i = 0, (settings.gridSize) do --left and right
        createObject(border, "resources/textures/snakeborder.png")
        moveObject(border, #border, 0, i)
        createObject(border, "resources/textures/snakeborder.png")
        moveObject(border, #border, (settings.gridSize + 1), i)
    end

    --create snake
    for i = 1, settings.startlen do
        createObject(snake, "resources/textures/box.png")
        moveObject(snake, i, (settings.startlen + 1) - i, 1)
    end
    snake[1].drawable:SetTexture("resources/textures/head.png")
    
    --create food
    createObject(food, "resources/textures/cherry.png")
    moveObject(food, 1, math.random(1, settings.gridSize), math.random(1, settings.gridSize))
end

function HookKeyPressed(key)
    if (key == "W" and direction ~= 2 and direction ~= 0) then -- 0 is up
        direction = 0
        moveTime = settings.updateTime
    elseif (key == "S" and direction ~= 0 and direction ~= 2) then -- 2 is down
        direction = 2
        moveTime = settings.updateTime
    elseif (key == "A" and direction ~= 3 and direction ~= 1) then -- 1 is left
        direction = 1
        moveTime = settings.updateTime
    elseif (key == "D" and direction ~= 1 and direction ~= 3) then -- 3 is right
        direction = 3
        moveTime = settings.updateTime
    end
end

function moveFood()
    local x = math.random(1, settings.gridSize)
    local y = math.random(1, settings.gridSize) 

    local done = false    

    while not done do
        local fine = true
        for i=1, #snake do
            if  x == snake[i].gridpos.x and y == snake[i].gridpos.y then
                    x = math.random(1, settings.gridSize)
                    y = math.random(1, settings.gridSize)
                    fine = false
                    break
            end
        end
        done = fine
    end

    moveObject(food, 1, x, y)
end

function checkFood()
    if snake[1].gridpos.x == food[1].gridpos.x and snake[1].gridpos.y == food[1].gridpos.y then
        createObject(snake, "resources/textures/box.png")
        moveFood()
    end
end

function checkWin()
    if #snake == settings.gridSize * settings.gridSize then
        print("WIN")
    end
end

function checkDeath()
    for i=2, #snake do
        if  snake[1].gridpos.x == snake[i].gridpos.x and 
            snake[1].gridpos.y == snake[i].gridpos.y then
                print("DEATH!!!")
        end
    end
end

function Think(dt)
    moveTime = moveTime + dt

    --snake[1] is the head cos arrays start at 1
    local head = snake[1]

    if (moveTime >= settings.updateTime) then --in seconds
        moveTime = 0

        local newY = head.gridpos.y
        local newX = head.gridpos.x

        if direction == 0 then newY = head.gridpos.y - 1            
        elseif direction == 1 then newX = head.gridpos.x - 1
        elseif direction == 2 then newY = head.gridpos.y + 1 
        elseif direction == 3 then newX = head.gridpos.x + 1 end

        if newX < 1 then newX = settings.gridSize
        elseif newX > settings.gridSize then newX = 1 end
        if newY < 1 then newY = settings.gridSize 
        elseif newY > settings.gridSize then newY = 1 end

        moveObject(snake, 1, newX, newY)

        for i=2, #snake do
            --local piece = snake[i]
            local oldpiece = snake[i-1]
            moveObject(snake, i, oldpiece.oldgridpos.x, oldpiece.oldgridpos.y)
        end

        checkWin()
        checkFood()
        checkDeath()
    end
end
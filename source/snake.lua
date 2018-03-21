local settings = {
    gridSize = 10,
    scale = 32,
    startlen = 9,
}

local snake = {}
local food = {}

function createPiece()
    local piece = {}

    piece.drawable = DrawableComponent.New()
    piece.drawable:SetTexture("resources/textures/box.png")

    piece.entity = Entity.New("piece" .. #snake)
    piece.entity:AddDrawable(piece.drawable)

    piece.gridpos = {x = -1, y = -1}
    piece.oldgridpos = {x = -1, y = -1}

    table.insert(snake, piece)
    
    return #snake --return the location of the piece
end

function createFood()
    local nfood = {}

    nfood.drawable = DrawableComponent.New()
    nfood.drawable:SetTexture("resources/textures/box.png")

    nfood.entity = Entity.New("piece" + #nfood)
    nfood.entity:AddDrawable(nfood.drawable)

    nfood.gridpos = {x= -1, y =-1}

    table.insert(food, nfood)

end

function movePiece(index, x, y)
    local piece = snake[index]
    piece.drawable:SetPos(x * settings.scale, y * settings.scale)
    
    piece.oldgridpos.x = piece.gridpos.x
    piece.oldgridpos.y = piece.gridpos.y

    piece.gridpos.x = x
    piece.gridpos.y = y
end

local direction = 3
local moveTime = 0
local updateTime = 0.5

function Init()
    for i = 1, settings.startlen do
        createPiece()
        movePiece(i, (settings.startlen + 1) - i, 1)
    end
    snake[1].drawable:SetTexture("resources/textures/head.png")
end

function HookKeyPressed(key)
    if (key == "W" and direction ~= 2 and direction ~= 0) then -- 0 is up
        direction = 0
        moveTime = updateTime
    elseif (key == "S" and direction ~= 0 and direction ~= 2) then -- 2 is down
        direction = 2
        moveTime = updateTime
    elseif (key == "A" and direction ~= 3 and direction ~= 1) then -- 1 is left
        direction = 1
        moveTime = updateTime
    elseif (key == "D" and direction ~= 1 and direction ~= 3) then -- 3 is right
        direction = 3
        moveTime = updateTime
    end
end

function Think(dt)
    moveTime = moveTime + dt

    --snake[1] is the head cos arrays start at 1
    local head = snake[1]

    if (moveTime >= updateTime) then --in seconds
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

        movePiece(1, newX, newY)

        for i=2, #snake do
            --local piece = snake[i]
            local oldpiece = snake[i-1]

            movePiece(i, oldpiece.oldgridpos.x, oldpiece.oldgridpos.y)
        end
    end

end
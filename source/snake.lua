
local snake = {}
local food = {}

function createPiece()

    local head = {}

    head.drawable = Drawable.New()
    head.drawable:SetTexture("resources/textures/box.png")

    head.entity = Entity.new("piece" + #snake)

    table.insert(snake, head)

end

function createFood()

    local food = {}

    food.drawable = Drawable.New()
    food.drawable:SetTexture("resources/textures/box.png")

    food.entity = Entity.new("piece" + #snake)

    table.insert(snake, food)

end

function Init()

end

function Think(dt)

    local xMove = 0
    local yMove = 0

    if (IsKeyPressed("W")) then
        yMove = yMove - 1
    end
    if (IsKeyPressed("S")) then
        yMove = yMove + 1
    end
    if (IsKeyPressed("A")) then
        xMove = xMove - 1
    end
    if (IsKeyPressed("D")) then
        xMove = xMove + 1
    end

    --move the head
    --place each part of the tail

end
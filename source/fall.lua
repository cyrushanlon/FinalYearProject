settings = {
    gravityY = -10
}

local downwall = {}
local boxes = {}

local mainView = Window.GetDefaultView()
local otherView = View.New(0, 0, 1280, 720, "otherView")

function createBox(x, y)

    local box = {}
    box.drawable = DrawableComponent.New()
    box.drawable:SetTexture("resources/textures/box.png")
    box.entity = Entity.New("ball"..#boxes)
    box.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            allowSleep = false,
            type = "dynamic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 1,
            restitution = 0.2--math.random( 50 ) / 100
        }),
        1, 1)
    box.entity:AddDrawable(box.drawable)
    box.entity:AddPhysics(box.physics)

    box.physics:SetPos(x, y)

    table.insert(boxes, box)
end

function Init()
    settings.windowSize = Window.GetSize()

    for y = 1, 15 do
        for x = 1, y do
            createBox(x , y)
        end
    end

    --downwall wall
    downwall.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active=true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 1,
        }),
        50, 10)

    downwall.drawable = DrawableComponent.New()
    downwall.drawable:SetTexture("resources/textures/floor.png")

    downwall.entity = Entity.New("downwall")
    downwall.entity:AddPhysics(downwall.physics)
    downwall.entity:AddDrawable(downwall.drawable)

    downwall.physics:SetPos(15, settings.windowSize.y / -32)

    local box = {}
    box.drawable = DrawableComponent.New()
    box.drawable:SetTexture("resources/textures/box.png")
    box.entity = Entity.New("testBox")
    box.entity:AddDrawable(box.drawable)
    box.drawable:SetViewTarget("otherView")
    box.drawable:SetPos(50,50)

    mainView:Move(-300, 0)
    mainView:Zoom(2)
end


function Think(dt)

    local xMove = 0
    local yMove = 0

    local zoom = 1

    if (IsKeyPressed("Right")) then
        xMove = xMove + 1000
    end
    if (IsKeyPressed("Left")) then
        xMove = xMove - 1000
    end
    if (IsKeyPressed("Up")) then
        yMove = yMove - 1000
    end
    if (IsKeyPressed("Down")) then
        yMove = yMove + 1000
    end

    if (IsKeyPressed("LControl")) then
        zoom = zoom - (0.5 * dt)
    end
    if (IsKeyPressed("LShift")) then
        zoom = zoom + (0.5 * dt)
    end

    mainView:Move(xMove * dt, yMove * dt)
    mainView:Zoom(zoom)
end
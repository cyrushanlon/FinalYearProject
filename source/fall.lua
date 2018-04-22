settings = {
    gravityY = -10,
    bgColor = 0xb541f4ff
}

local downwall = {}
local boxes = {}

local mainView = Window.GetDefaultView()
local otherView = View.New(0, 0, 1280, 720, "otherView")

local count = 0

function HookKeyPressed(key)
    if (key == "Space") then
        reset()
    end
end

function reset()

    count = 1
    for y = 1, 15 do
        for x = 1, y do
            local box = boxes[count].physics
            box:SetPos(x, y)
            box:SetVel(0,0)
            box:SetAng(0)

            count = count + 1
        end
    end
end

function createBox()

    local box = {}
    box.drawable = DrawableComponent.New()
    box.drawable:SetTexture("resources/textures/box.png")
    box.entity = Entity.New("ball"..#boxes)
    box.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            --allowSleep = false,
            type = "dynamic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 1,
            restitution = 0.3--math.random( 50 ) / 100
        }),
        1, 1)
    box.entity:AddDrawable(box.drawable)
    box.entity:AddPhysics(box.physics)

    count = count + 1
    boxes[count] = box
end

function Init()
    settings.windowSize = Window.GetSize()

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

    --set view position and zoom level
    mainView:Move(-300, 0)
    mainView:Zoom(2)

    for y = 1, 120 do
        createBox()
    end
    reset()
end

function Think(dt)

    local xMove = 0
    local yMove = 0

    local zoom = 1

    if (IsKeyPressed("D")) then
        xMove = xMove + 1000
    end
    if (IsKeyPressed("A")) then
        xMove = xMove - 1000
    end
    if (IsKeyPressed("W")) then
        yMove = yMove - 1000
    end
    if (IsKeyPressed("S")) then
        yMove = yMove + 1000
    end

    

    if (IsKeyPressed("Y")) then
        for y = 1, 120 do
            boxes[y].physics:ApplyAngularImpulse(0.1, true)
        end
    end
        

    if (IsKeyPressed("LControl")) then
        zoom = zoom + (0.5 * dt)
    end
    if (IsKeyPressed("LShift")) then
        zoom = zoom - (0.5 * dt)
    end

    if (xMove ~= 0 or yMove ~= 0) then
        mainView:Move(xMove * dt, yMove * dt)
    end
    if (zoom ~= 1) then
        mainView:Zoom(zoom)
    end
end
settings = {
    gravityY = -10
}

local downwall = {}
local boxes = {}

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
            createBox(x+8 , y)
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
end


function Think(dt)

end
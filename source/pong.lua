settings = {
    gravityY = -10
}

settings.maxspeed = 1500
settings.speedmultval = 300

--objects
local floor = {}
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
            friction= 0.3,
            restitution = 0.5
        }),
        2, 2)
    box.entity:AddDrawable(box.drawable)
    box.entity:AddPhysics(box.physics)

    box.physics:SetPos(x, y)

    boxes[#boxes] = box
end

function Init()
    settings.windowSize = Window.GetSize()

    

    --left wall
    leftwall.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active=true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.3,
        }),
        1, 100)
    leftwall.entity = Entity.New("leftwall")
    leftwall.entity:AddPhysics(leftwall.physics)

    --right wall
    rightwall.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active=true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.3,
        }),
        1, 100)
        rightwall.entity = Entity.New("rightwall")
        rightwall.entity:AddPhysics(rightwall.physics)
        rightwall.physics:SetPos(settings.windowSize.x / 32,0)
end

function Think(dt)

    local mousepos = GetMousePos()

    local paddlesize = paddle.drawable:GetSize()

    if mousepos.x - paddlesize.x/2 < 0 then
        mousepos.x = paddlesize.x/2
    elseif mousepos.x > settings.windowSize.x - paddlesize.x/2 then
        mousepos.x = settings.windowSize.x - paddlesize.x/2
    end

    paddle.physics:SetPos(mousepos.x / 32, paddle.y)

end
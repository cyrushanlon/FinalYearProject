settings = {
    gravityY = -10
}

settings.maxspeed = 1500
settings.speedmultval = 300

local sounds = {}

--objects
local paddle = {}
local ball = {}

local leftwall = {}
local rightwall = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()
    settings.windowSize = Window.GetSize()

    ball.drawable = DrawableComponent.New()
    ball.drawable:SetTexture("resources/textures/ball.png")
    ball.entity = Entity.New("ball1")
    ball.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active = true,
            allowSleep = false,
            type = "dynamic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.3,
            restitution = 1.2
        }),
        1, 1)
    ball.entity:AddDrawable(ball.drawable)
    ball.entity:AddPhysics(ball.physics)
    
    paddle.drawable = DrawableComponent.New()
    paddle.drawable:SetTexture("resources/textures/paddle.png")
    paddle.entity = Entity.New("paddle1")
    paddle.physics = PhysicsComponent.New(
        b2BodyDef.New({
            active=true,
            type = "kinematic"
        }),
        b2FixtureDef.New({
            density = 1,
            friction= 0.3,
        }),
        2, 0.1)
    paddle.entity:AddDrawable(paddle.drawable)
    paddle.entity:AddPhysics(paddle.physics)

    paddle.y = (settings.windowSize.y /-32) + 1
    ball.physics:SetPos(5, 0)

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

    --load the sounds into the sound table
    --sounds.hitPaddle = Sound.New("hitPaddle", "resources/sounds/ping_pong_8bit_beep_paddle.wav")
    --sounds.hitWall = Sound.New("hitWall", "resources/sounds/ping_pong_8bit_beep_wall.wav")
    --sounds.hitLose = Sound.New("hitLose", "resources/sounds/ping_pong_8bit_beep_lose.wav")
end

function MoveBall(dt)

    local xTranslate = 0
    local yTranslate = 0

    local pos = ball.obj:GetPos()
    ball.obj:SetPos(pos.x + (ball.vel.x * dt), pos.y + (ball.vel.y * dt))

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
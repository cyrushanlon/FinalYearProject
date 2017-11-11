local settings = {}

settings.paddle = {}
settings.paddle.y = 100
settings.paddle.depth = 0
settings.maxspeed = 1500
settings.speedmultval = 300

local sounds = {}

--objects
local paddle
local ball = {
    vel = {x = -50, y = 500}
}

function HookLostFocus()
    print("lost")
end

function HookGainedFocus()
    print("gained")
end

function Init()
    settings.windowSize = Window.GetSize()

    paddle = Drawable.New("paddle1", "resources/textures/paddle.png");
    ball.obj = Drawable.New("ball1", "resources/textures/ball.png") -- we put this in .obj so we can have other lua vars in the overarching table

    settings.paddle.pos = settings.windowSize.y - settings.paddle.y

    --load the sounds into the sound table
    sounds.hitPaddle = Sound.New("resources/sounds/ping_pong_8bit_beep_paddle.wav")
    sounds.hitWall = Sound.New("resources/sounds/ping_pong_8bit_beep_wall.wav")
    sounds.hitLose = Sound.New("resources/sounds/ping_pong_8bit_beep_lose.wav")
end

function MoveBall(dt)

    local xTranslate = 0
    local yTranslate = 0

    local pos = ball.obj:GetPos()
    ball.obj:SetPos(pos.x + (ball.vel.x * dt), pos.y + (ball.vel.y * dt))

end

function PhysThink(dt)

    local ballPos = ball.obj:GetPos()
    local paddlePos = paddle:GetPos()
    local ballSize = ball.obj:GetSize()
    local paddleSize = paddle:GetSize()

    --------------
    --AABB check on ball and paddle, this could be replaced with box2d but that might be considered overkill in this case
    --the ball bounces off the sides and top too

    --vertical bounce
    if  ballPos.x < paddlePos.x + paddleSize.x and
        ballPos.x + ballSize.x > paddlePos.x and
        ballPos.y + ballSize.y > settings.paddle.pos + settings.paddle.depth or 
        ballPos.y < 0 then

        if not (ballPos.y < 0) then -- top of screen bounce
            --scale x velocity based on distance from center of paddle
            local paddleCenter = paddlePos.x + (paddleSize.x / 2)
            local ballCenter = ballPos.x + (ballSize.x / 2)
            local maxDistance = paddleSize.x / 2

            local mult = ((paddleCenter - ballCenter) / -maxDistance)

            ball.vel.x = ball.vel.x + (settings.speedmultval * mult)
            ball.vel.y = ball.vel.y * (1 + math.abs(mult))
        end

        ball.vel.y = -ball.vel.y
        sounds.hitWall:Play()
    end

    -- horizontal bounce
    if  ballPos.x < 0 or 
        ballPos.x + ballSize.x > settings.windowSize.x then

        ball.vel.x = -ball.vel.x
    end     
    ---------------

    --speed clipping
    if ball.vel.x > settings.maxspeed then
        ball.vel.x = settings.maxspeed
    elseif ball.vel.y > settings.maxspeed then
        ball.vel.y = settings.maxspeed
    elseif ball.vel.x < -settings.maxspeed then
        ball.vel.x = -settings.maxspeed
    elseif ball.vel.y < -settings.maxspeed then
        ball.vel.y = -settings.maxspeed
    end

    MoveBall(dt)

end

function Think(dt)

    PhysThink(dt)

    local mousepos = GetMousePos()
    if mousepos.x < 0 then
        mousepos.x = 0
    elseif mousepos.x > settings.windowSize.x - paddle:GetSize().x then
        mousepos.x = settings.windowSize.x - paddle:GetSize().x
    end

    paddle:SetPos(mousepos.x, settings.paddle.pos)

end
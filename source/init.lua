local settings = {}

--these should using a C++ func call
settings.paddle = {w = 74, h = 15}
settings.ball = {w = 32, h = 32}
settings.window = {w = 1920, h = 1080}
--

settings.paddle.y = 100
settings.paddle.depth = 0
settings.maxspeed = 500
settings.speedmultval = 300

local paddle
local ball = {
    vel = {x = -50, y = 150}
}

function Init()
    paddle = Drawable.New("paddle1", "resources/textures/paddle.png");
    ball.obj = Drawable.New("ball1", "resources/textures/ball.png") -- we put this in .obj so we can have other lua vars in the overarching table

    settings.paddle.pos = settings.window.h - settings.paddle.y
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

    --AABB check on ball and paddle, this could be replaced with box2d but that might be considered overkill in this case
    --the ball bounces off the sides and top too

    --vertical bounce
    if  ballPos.x < paddlePos.x + settings.paddle.w and
        ballPos.x + settings.ball.w > paddlePos.x and
        ballPos.y + settings.ball.h > settings.paddle.pos + settings.paddle.depth or 
        ballPos.y < 0 then

        if not (ballPos.y < 0) then -- top of screen bounce
            --scale x velocity based on distance from center of paddle
            local paddleCenter = paddlePos.x + (settings.paddle.w / 2)
            local ballCenter = ballPos.x + (settings.ball.w / 2)
            local maxDistance = settings.paddle.w / 2

            local mult = ((paddleCenter - ballCenter) / -maxDistance)

            ball.vel.x = ball.vel.x + (settings.speedmultval * mult)
            ball.vel.y = ball.vel.y * (1 + mult)
        end

        ball.vel.y = -ball.vel.y
    end

    -- horizontal bounce
    if  ballPos.x < 0 or 
        ballPos.x + settings.ball.w > settings.window.w then

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

    --there seems to be a case where vel is set to 0
    if ball.vel.y < 1 and ball.vel.y > -1 then
        ball.vel.y = 1
    end

    MoveBall(dt)

end

function Think(dt)

    PhysThink(dt)

    local mousepos = GetMousePos()
    if mousepos.x < 0 then
        mousepos.x = 0
    elseif mousepos.x > settings.window.w - settings.paddle.w then
        mousepos.x = settings.window.w - settings.paddle.w
    end

    paddle:SetPos(mousepos.x, settings.paddle.pos)

    print(ball.vel.x, ball.vel.y, 1/dt)

end
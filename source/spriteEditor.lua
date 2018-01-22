local settings = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()

end

local objects = {}

local walkAnim = Animation.New("walk", "resources/textures/metalslug_mummy37x45.png", 37, 45, 50, 18)
walkAnim:SetFirstFrameTopLeft(0, 0);
walkAnim:SetLooping(true);
--idleAnim:SetBackgroundColor(sf::Color::White);
walkAnim:Regenerate();

for i=1, 1 do 
    local testAnimatable = Animatable.New("test"..i, "2")
    --testAnimatable:SetPos(i*37, 0)

    testAnimatable:AddAnimation("walk", walkAnim)
    testAnimatable:SetAnimation("walk")

    objects[1] = testAnimatable
end

local pressed = false
local lastPressed = false

function Think(dt)

    --print(1/dt)

    lastPressed = pressed

    if (IsKeyPressed("W")) then
        pressed = true
    else
        pressed = false
    end
    
    if (lastPressed ~= pressed) then
        print(pressed)
        if (pressed) then
            testAnimatable:SetAnimation("walk", walkAnim)
        else
            testAnimatable:SetAnimation("idle")
        end
    end

end
local settings = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()

end

local testAnimatable = Animatable.New("test1")

local idleAnim = Animation.New("walk", "resources/textures/character_sheet.png", 400, 600, 10, 1)
idleAnim:SetFirstFrameTopLeft(0, 0);
idleAnim:SetLooping(true);
--idleAnim:SetBackgroundColor(sf::Color::White);
idleAnim:Regenerate();

local walkAnim = Animation.New("walk", "resources/textures/character_sheet.png", 400, 600, 10, 4)
walkAnim:SetFirstFrameTopLeft(0, 0);
walkAnim:SetLooping(true);
--idleAnim:SetBackgroundColor(sf::Color::White);
walkAnim:Regenerate();

testAnimatable:AddAnimation("idle", idleAnim)
testAnimatable:AddAnimation("walk", walkAnim)
testAnimatable:SetAnimation("idle")

local pressed = false
local lastPressed = false

function Think(dt)

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
local settings = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()

end

local idleAnim = Animation.New("idle", "resources/textures/character_sheet.png", 400, 600, 10, 4)
idleAnim:SetFirstFrameTopLeft(0, 0);
idleAnim:SetLooping(true);
--idleAnim:SetBackgroundColor(sf::Color::White);
idleAnim:Regenerate();

function Think(dt)

end
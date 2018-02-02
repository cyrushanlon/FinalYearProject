local settings = {}
local objects = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()
    local testEnt1 = Entity.New("testEnt1")
    local testDrc1 = DrawableComponent.New()

    testDrc1:SetPos(100,100)

    testEnt1:AddComponent(testDrc1)
    testDrc1:SetTexture("resources/textures/metalslug_mummy37x45.png")
end


local pressed = false
local lastPressed = false

function Think(dt)

end
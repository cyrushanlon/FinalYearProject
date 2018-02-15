local settings = {}
local objects = {}
local comps = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function Init()
    local testEnt1 = Entity.New("testEnt1")
    local testDrc1 = DrawableComponent.New()
    local anim = Animation.New("walk", "resources/textures/metalslug_mummy37x45.png", 37, 45, 50, 18)
    anim:SetLooping(true)
    anim:Regenerate()

    testDrc1:AddAnimation(anim)
    testDrc1:SetAnimation("walk")
    testDrc1:SetAnimates(true)
    testDrc1:SetOrigin(18, 22)

    testEnt1:AddComponent(testDrc1)

    comps["testEnt1"] = testDrc1
    
    local bodydef = b2BodyDef.New({
        active=true,
    })
end


local pressed = false
local lastPressed = false

function Think(dt)
    local pos = GetMousePos()

    comps["testEnt1"]:SetPos(pos.x, pos.y)
end
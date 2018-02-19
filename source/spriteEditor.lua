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
    testDrc1:SetTexture("resources/textures/box.png")
    --local anim = Animation.New("walk", "resources/textures/metalslug_mummy37x45.png", 37, 45, 50, 18)
    --anim:SetLooping(true)
    --anim:Regenerate()
    --testDrc1:AddAnimation(anim)
    --testDrc1:SetAnimation("walk")
    --testDrc1:SetAnimates(true)
    --testDrc1:SetOrigin(18, 22)

    local testPhy1 = PhysicsComponent.New(
    b2BodyDef.New({
        active=true,
        type = "b2_dynamicBody"
    }),
    b2FixtureDef.New({
        density = 1,
        friction= 0.3,
    }),
    4, 4)

    testEnt1:AddDrawable(testDrc1)
    testEnt1:AddPhysics(testPhy1)

    comps["testEnt1dc"] = testDrc1
    comps["testEnt1ph"] = testPhy1
    objects["testEnt"] = testEnt1

end

function Think(dt)
    local pos = GetMousePos()

    comps["testEnt1ph"]:SetPos(pos.x / 32, -pos.y / 32)
end
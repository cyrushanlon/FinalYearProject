local settings = {}
local objects = {}
local comps = {}

function HookLostFocus()
end

function HookGainedFocus()
end

function HookKeyReleased(x)
    print(x .. " release")
end

function HookKeyPressed(x)
    print(x .. " pressed")
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
        type = "dynamic"
    }),
    b2FixtureDef.New({
        density = 1,
        friction= 0.3,
    }),
    4, 4)

    testPhy1:SetPos(5,-2)

    testEnt1:AddDrawable(testDrc1)
    testEnt1:AddPhysics(testPhy1)

    comps["testEnt1dc"] = testDrc1
    comps["testEnt1ph"] = testPhy1
    objects["testEnt"] = testEnt1

end

local ang = 0

function getMag(x, y)
    return math.sqrt(math.pow(x, 2) + math.pow(y, 2))
end

function Think(dt)
    local mpos = GetMousePos()
    --transform mouse pos to box2d pos
    mpos.x = mpos.x / 32
    mpos.y = mpos.y / -32

    local comp = comps["testEnt1ph"]
    
    --find vector from box to mouse 
    local bpos = comp:GetPos()
    local x = mpos.x - bpos.x
    local y = mpos.y - bpos.y
    local magnitude = getMag(x, y)
    x = x / magnitude
    y = y / magnitude

    local vel = comp:GetVel()
    local speed = getMag(vel.x, vel.y)

    comp:ApplyImpulse(x, y, true)
end
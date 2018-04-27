box.physics = PhysicsComponent.New(
    b2BodyDef.New({
        active = true,
        type = "dynamic"
    }),
    b2FixtureDef.New({
        density = 1,
        friction= 1,
        restitution = 0.3
    }),
    1, 1)

    local ss = "resources/textures/metalslug_mummy37x45.png"

    local anim = Animation.New("walk", ss, 37, 45, 50, 18)
    anim:SetLooping(true)
    anim:Regenerate()

    local testDrc1 = DrawableComponent.New()
    testDrc1:SetOrigin(18, 22)
    testDrc1:AddAnimation(anim)
    testDrc1:SetAnimation("walk")
    testDrc1:SetAnimates(true)
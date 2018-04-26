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
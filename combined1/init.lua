local drawable = Drawable.New("ID1", "resources/textures/smile.png");
print(drawable:GetPos().x, drawable:GetPos().y)
drawable:SetPos(100, 100)
print(drawable:GetPos().x, drawable:GetPos().y)

function Think(dt)

    print(1/dt)
    local pos = drawable:GetPos()
    drawable:SetPos(pos.x, pos.y + 100 * dt)

end
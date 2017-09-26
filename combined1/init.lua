local drawable

function Init()
    drawable = Drawable.New("ID1", "resources/textures/smile.png");
    drawable:SetPos(100, 100)
end



function Think(dt)

    print(1/dt)
    local pos = drawable:GetPos()
    drawable:SetPos(pos.x, pos.y + 100 * dt)

end
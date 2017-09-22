local drawable = Drawable.New("ID1", "resources/textures/smile.png");
print(drawable:GetPos().x, drawable:GetPos().y)
drawable:SetPos(100, 100)
print(drawable:GetPos().x, drawable:GetPos().y)
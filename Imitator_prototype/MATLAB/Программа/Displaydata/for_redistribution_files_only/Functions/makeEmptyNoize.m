% --- Создается пустая цель шума
function makeEmptyNoize()
    Noize.x = [];
    Noize.y = [];
    Noize.z = [];
    Noize.Vr = [];
    Noize.t = [];
    assignin('base','Noize',Noize);
   
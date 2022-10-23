local M = Unlua.Class();

function M:ReceiveConstruct()
    -- Get Data
    self.Exp = {100,1500,2500}
    self.MaxExp = {200,2000,3000}
    self.Progress = {self.ProgressBar_0, self.ProgressBar_1, self.ProgressBar_2,self.ProgressBar_3}

    -- If No Change, Go Next

    BindInit()
    OnUpdatePage();
    UpdatePage();
end
function ReceiveTick(DeltaTime)
    for i,v in ipairs(self.Exp) do
        self.CurVal[i] = v / MaxExp[i] * self.AnimTime
        self.Progress[i].SetPercent(self.CurVal[i]);
    end
end

function M:BindInit()
    -- OnSkip
    -- OnContinue

    -- OnUpdatePage
end

function M:OnSkip()

end

function M:OnContinue()

end

function M:UpdateProgress()

end

function M:UpdatePage()
    -- body
end
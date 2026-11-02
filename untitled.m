addr = "USB0::0x2A8D::0x039B::CN64501194::0::INSTR";
v = visadev(addr);
v.Timeout = 5;

writeline(v, "*CLS");
writeline(v, ":ACQuire:TYPE NORMal");         % 평균(Average) 모드면 매우 느려짐
writeline(v, ":TRIGger:SWEep AUTO");
writeline(v, ":WAVeform:SOURce CHANnel1");
writeline(v, ":WAVeform:FORMat BYTE");
writeline(v, ":WAVeform:POINts:MODE NORMal");
writeline(v, ":WAVeform:POINts 500");         % 점 수를 줄이면 빨라짐
writeline(v, ":RUN");                         % DIGitize 안 씀 → 스코프는 계속 동작

% 스케일 정보는 한 번만 읽기
pre  = str2double(split(strtrim(writeread(v, ":WAVeform:PREamble?")), ","));
xinc = pre(5); xorg = pre(6); xref = pre(7);
yinc = pre(8); yorg = pre(9); yref = pre(10);
t = ((0:pre(3)-1) - xref) * xinc + xorg;

% y축을 스코프 화면 범위로 고정 (매 프레임 자동 스케일 방지)
vdiv = str2double(writeread(v, ":CHANnel1:SCALe?"));
voff = str2double(writeread(v, ":CHANnel1:OFFSet?"));

fig = figure('Name', 'EDUX1052G 실시간');
h = plot(t, nan(size(t))); grid on
xlim([t(1) t(end)]); ylim(voff + [-4 4]*vdiv);
xlabel('시간 (s)'); ylabel('전압 (V)');
cnt = 0; tic;

while isvalid(fig)
    writeline(v, ":WAVeform:DATA?");
    raw = double(readbinblock(v, "uint8"));
    flush(v, "input");

    if ~isvalid(fig), break; end
    if numel(raw) ~= numel(t)                 % 스코프 설정이 바뀌면 다시 계산
        pre  = str2double(split(strtrim(writeread(v, ":WAVeform:PREamble?")), ","));
        xinc = pre(5); xorg = pre(6); xref = pre(7);
        yinc = pre(8); yorg = pre(9); yref = pre(10);
        t = ((0:numel(raw)-1) - xref) * xinc + xorg;
        set(h, 'XData', t); xlim([t(1) t(end)]);
    end

    h.YData = (raw - yref) * yinc + yorg;
    cnt = cnt + 1;
    if mod(cnt, 20) == 0                      % 제목은 가끔만 갱신
        title(sprintf('CH1  |  %.1f fps', cnt / toc));
    end
    drawnow limitrate
end
clear v
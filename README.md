# NaturalVoiceSAPIAdapter

An [SAPI 5 text-to-speech (TTS) engine][1] that can utilize the [natural/neural voices][2] provided by the [Azure AI Speech Service][3], including:

- Installable natural voices for Narrator on Windows 11
- Online natural voices from Microsoft Edge's Read Aloud feature
- Online natural voices from the Azure AI Speech Service, if you have a proper subscription key

Any program that supports SAPI 5 voices can use those natural voices via this TTS engine.

See the [wiki pages][4] for some more technical information.

## ���

���� [Azure AI ��������][3]��ʹ����������Ҳ��ʹ��΢��[��Ȼ����][2]�� [SAPI 5 TTS ����][1]��֧��������Ȼ������

- Windows 11 �еĽ�������Ȼ����
- Microsoft Edge �С������ʶ������ܵ�������Ȼ����
- ���� Azure AI ���������������Ȼ������ֻҪ���ж�Ӧ�� key

�κ�֧�� SAPI 5 �����ĳ��򶼿��Խ���������ʹ����������Ȼ������

���༼����ص���Ϣ���Բ��� [wiki ҳ��][4]��

## System Requirements

Windows XP SP3, or later versions of Windows. x86 32/64-bit.

**I'm using Windows 10. Can I use the Narrator natural voices on Windows 11?**

Yes, as long as your Windows 10 build number is 17763 or above (version 1809). You can choose and install Windows 11 Narrator voices [here][5].

Windows 10's Narrator doesn't support natural voices directly, but it does support SAPI 5 voices. So you can make Windows 11 Narrator voices work on Windows 10 via this engine.

**Does it really work on Windows XP?**

Yes, although I only tested it on a virtual machine.

On Windows XP, Windows 11 Narrator voices don't work. But online Microsoft Edge voices and Azure voices work.

**Will it work on future versions of Windows?**

This engine uses some encryption keys extracted from system files to use the voices, so it's more like a hack than a proper solution.

As for now, Microsoft hasn't yet allowed third-party apps to use the Narrator/Edge voices, and this can stop working at any time, for example, after a system update.

## ϵͳҪ��

Windows XP SP3 ����߰汾��x86 32/64 λ��

**���õ� Windows 10 ϵͳ������ʹ�� Windows 11 ϵͳ�Ľ�������Ȼ������**

���ԣ�ֻҪϵͳ�汾Ϊ 1809 ����°汾������ת��[����][5]���ذ�װ Windows 11 ϵͳ�Ľ�������Ȼ������

Windows 10 ϵͳ�Ľ����˲���֧����Ȼ����������֧�� SAPI 5 ���������Կ��Խ������������� Windows 10 ϵͳ�Ľ�����Ҳ֧����Ȼ������

**Windows XP ��������ã�**

���ԣ���Ȼ��ֻ��������ϲ��Թ���

XP �Ͻ�������Ȼ���������ã����� Edge �� Azure ������������Ȼ���á�

**֮��� Windows �汾��������**

������ʹ���˴�ϵͳ�ļ�����ȡ�Ľ�����Կ��ʹ���������Ⲣ���ǹٷ��Ͽɵ���Ϊ��

Ŀǰ΢��û���������������ʹ�ý����������� Edge ��������ˣ���������ʱ���ܻ���ĳ��ϵͳ���º�ֹͣ������

## Installation

1. Download the zip file from the [Releases][6] section.
2. Extract the files in a folder. Make sure not to move or rename the files after installation.
3. Run the `install.bat` file **as administrator**.
4. If you are using this on Windows XP, you can also merge the `PhoneConverters.reg` file to make the system support more TTS languages.
5. Run the `uninstall.bat` file as administrator when you want to uninstall it.

Or, you can use `regsvr32` to register the DLL files manually.

## ��װ

1. �� [Releases][6] ������ zip �ļ���
2. ��ѹ��һ���ļ��С���װ��ɺ󣬲�Ҫ���ƶ�����������Щ�ļ���
3. **�Թ���Ա���**���� `install.bat`��
4. ���� Windows XP ��ʹ�ã����Ժϲ� `PhoneConverters.reg` ����ϵͳ֧�ָ����������ԡ�
5. ��Ҫж�أ��Թ���Ա������� `uninstall.bat`��

Ҳ������ `regsvr32` �ֶ�ע�� DLL �ļ���

## Testing

You can use the `TtsApplication-x86.exe` and `TtsApplication-x64.exe` to test the engine.

It's a modified version of the [TtsApplication in Windows-classic-samples][7], which added Chinese translation, and more detailed information for phoneme/viseme events.

## ����

����ʹ�� `TtsApplication-x86.exe` �� `TtsApplication-x64.exe` �����Ա����档

��������޸��� [Windows-classic-samples �е� TtsApplication][7]����������ķ���͸���ϸ�����ؿ����¼���Ϣ��

## Libraries used
- Microsoft.CognitiveServices.Speech.Extension.Embedded.TTS
- [websocketpp](https://github.com/zaphoyd/websocketpp)
- ASIO (standalone version)
- OpenSSL
- [nlohmann/json](https://github.com/nlohmann/json)
- [YY-Thunks](https://github.com/Chuyu-Team/YY-Thunks) (for Windows XP compatibility)

[1]: https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms717037(v=vs.85)
[2]: https://speech.microsoft.com/portal/voicegallery
[3]: https://learn.microsoft.com/azure/ai-services/speech-service/
[4]: https://github.com/gexgd0419/NaturalVoiceSAPIAdapter/wiki
[5]: https://github.com/gexgd0419/NaturalVoiceSAPIAdapter/wiki/Narrator-natural-voice-download-links
[6]: https://github.com/gexgd0419/NaturalVoiceSAPIAdapter/releases
[7]: https://github.com/microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/winui/speech/ttsapplication
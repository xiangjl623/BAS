#ifndef MAINAPP_H
#define MAINAPP_H
#include "include/cef_app.h"
#include "mainhandler.h"
#include "devtoolshandler.h"
#include "proxydata.h"
#include "cookievisitor.h"
#include "browserdata.h"
#include "v8handler.h"
#include "elementcommand.h"
#include "browsereventsemulator.h"
#include "toolboxhandler.h"
#include "scenariohandler.h"
#include "centralhandler.h"
#include <ctime>
#include "mainlayout.h"
#include "toolboxv8handler.h"
#include "scenariov8handler.h"
#include "centralv8handler.h"
#include "variablesextractor.h"
#include "extract_functions.h"
#include "extract_resources.h"
#include "settings.h"
#include "handlersmanager.h"


class MainApp: public CefApp, public CefBrowserProcessHandler, public CefRenderProcessHandler
{
    std::shared_ptr<HandlersManager> _HandlersManager;

    CefRefPtr<ToolboxHandler> thandler;
    CefRefPtr<ScenarioHandler> shandler;
    CefRefPtr<CentralHandler> chandler;
    CefRefPtr<CefBrowser> BrowserToolbox;
    CefRefPtr<CefBrowser> BrowserScenario;
    CefRefPtr<CefBrowser> BrowserCentral;
    CefRefPtr<DevToolsHandler> dhandler;
    CefRefPtr<CookieVisitor> cookievisitor;
    CefRefPtr<V8Handler> v8handler;
    CefRefPtr<ToolboxV8Handler> toolboxv8handler;
    CefRefPtr<ScenarioV8Handler> scenariov8handler;
    CefRefPtr<CentralV8Handler> central8handler;
    ElementCommand LastCommand;
    bool IsLastCommandNull;
    BrowserData *Data;
    settings* Settings;
    int ScrollX;
    int ScrollY;

    //MouseMove
    bool IsMouseMoveSimulation;
    float Speed;
    int MouseStartX;
    int MouseStartY;
    int MouseEndX;
    int MouseEndY;

    //MouseTrack
    clock_t LastMouseTrack;


    //TypeTextTask
    bool TypeTextTaskIsActive;
    int TypeTextX;
    int TypeTextY;
    bool TypeTextIsFirstLetter;
    std::string TypeText;
    KeyState TypeTextState;

    //Parent
    int ParentWidth;
    int ParentHeight;

    //Render
    bool NeedRenderNextFrame;
    int SkipBeforeRenderNextFrame;
    bool IsElementRender;
    int RenderX,RenderY,RenderWidth,RenderHeight;

    //Load
    bool IsWaitingForLoad;

    std::string DelayedSend;

    std::string SetNextActionId;

    int TypeTextDelay;
    int TypeTextDelayCurrent;
    clock_t TypeTextLastTime;

    void InitBrowser();
    std::string NextLoadPage;
    std::vector<char> ImageData;
    int ImageWidth;
    int ImageHeight;
    MainLayout *Layout;

    std::string Code, Resources, AdditionalResources, Variables, Functions;
    bool ResourcesChanged;
    void UpdateScrolls(std::string& data);
    void HandleMainBrowserEvents();
    void HandleToolboxBrowserEvents();
    void HandleScenarioBrowserEvents();
    void HandleCentralBrowserEvents();


    std::string Lang;

    int RunElementCommandCallbackOnNextTimer;

public:
    MainApp();
    void ForceUpdateWindowPositionWithParent();
    void UpdateWindowPositionWithParent();
    void SetData(BrowserData *Data);
    void SetSettings(settings *Settings);
    void SetLayout(MainLayout *Layout);
    BrowserData * GetData();
    std::vector<std::string> GetAllPopupsUrls();

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;

    virtual void OnBeforeCommandLineProcessing(const CefString& process_type,CefRefPtr<CefCommandLine> command_line) OVERRIDE;
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) OVERRIDE;
    virtual void OnWebKitInitialized() OVERRIDE;

    virtual void OnContextInitialized() OVERRIDE;
    bool IsNeedQuit();

    //EventCallbacks
    void LoadCallback(const std::string& page);
    void ResetCallback();
    void ResetCallbackFinalize();

    void SetNextActionCallback(const std::string& NextActionId);
    void TimezoneCallback(int offset);
    void GeolocationCallback(float latitude, float longitude);
    void VisibleCallback(bool visible);
    void SetProxyCallback(const std::string& server, int Port, bool IsHttp, const std::string& username, const std::string& password);
    void AddHeaderCallback(const std::string& key,const std::string& value);
    void CleanHeaderCallback();
    void GetUrlCallback();
    void SetUserAgentCallback(const std::string& value);
    void SetOpenFileNameCallback(const std::string& value);
    void SetStartupScriptCallback(const std::string& value);
    void SetPromptResultCallback(const std::string& value);
    void SetHttpAuthResultCallback(const std::string& login,const std::string& password);
    void GetCookiesForUrlCallback(const std::string& value);
    void SaveCookiesCallback();
    void RestoreCookiesCallback(const std::string& value);
    void IsChangedCallback();

    void CrushCallback();
    void AddCacheMaskAllowCallback(const std::string& value);
    void AddCacheMaskDenyCallback(const std::string& value);
    void AddRequestMaskAllowCallback(const std::string& value);
    void AddRequestMaskDenyCallback(const std::string& value);
    void ClearCacheMaskCallback();
    void ClearRequestMaskCallback();
    void ClearLoadedUrlCallback();
    void ClearCachedDataCallback();
    void ScrollCallback(int x, int y);
    void RenderCallback(int x, int y, int width, int height);
    void ClearAllCallback();
    void ClearMasksCallback();
    void ClearDataCallback();
    void WaitCodeCallback();
    void StartSectionCallback(int);
    void ScriptFinishedCallback();
    void FindCacheByMaskBase64Callback(const std::string& value);
    void FindStatusByMaskCallback(const std::string& value);
    void FindCacheByMaskStringCallback(const std::string& value);
    void IsUrlLoadedByMaskCallback(const std::string& value);
    void GetLoadStatsCallback();
    void ElementCommandCallback(const ElementCommand &Command);
    void SetCodeCallback(const std::string & code);
    void SetResourceCallback(const std::string & resources);
    void SetInitialStateCallback(const std::string & lang);
    void DebugVariablesResultCallback(const std::string & data);

    void MouseClickCallback(int x, int y);
    void MouseClickUpCallback(int x, int y);
    void MouseClickDownCallback(int x, int y);
    void PopupCloseCallback(int index);
    void PopupSelectCallback(int index);
    void MouseMoveCallback(int x, int y);
    void LoadSuccessCallback();
    void ResizeCallback(int width, int height);
    void SetWindowCallback(const std::string& Window);

    void UrlLoaded(const std::string&, int);
    void AfterReadyToCreateBrowser(bool Reload);
    void Timer();
    void CefMessageLoop();
    void ExecuteTypeText();
    void ExecuteMouseMove();
    void FinishedLastCommand(const std::string& data);
    void Paint(char * data, int width, int height);
    void OldestRequestTimeChanged(int64 OldestTime);
    char* GetImageData();
    std::pair<int,int> GetImageSize();
    void CreateTooboxBrowser();
    void CreateScenarioBrowser();
    void CreateCentralBrowser();

    void EmulateClick(int x, int y);
    void EmulateMove(int x, int y);
    void EmulateMoveAndClick(int x, int y);
    void EmulateDrag(int x, int y);
    void EmulateDrop(int x, int y);

    //Tabs
    void AddTab();
    void SelectTab(int i);
    void CloseTab(int i);

    //Events
    std::vector<std::function<void(const std::string&)> > EventSendTextResponce;

    void Hide();
    void Terminate();
    void Restart();
    void ToggleDevTools();
    std::pair<int,int> GetScrollPosition();
    void ScrollUp();
    void ScrollDown();
    void ScrollLeft();
    void ScrollRight();

    void InspectAt(int x, int y);

    void MouseMoveAt(int x, int y);
    void MouseLeave();

    //Element Subtasks
    void ExecuteElementFunction(const std::string& FuncName);
    void ExecuteElementLoopFunction(const std::string& FuncName);

    void LoadSettingsPage();

private:
    void SendTextResponce(const std::string&);

    void GetCookiesForUrlCompleteCallback();
    void SaveCookiesCompleteCallback();

private:
    IMPLEMENT_REFCOUNTING(MainApp);
};

#endif // MAINAPP_H


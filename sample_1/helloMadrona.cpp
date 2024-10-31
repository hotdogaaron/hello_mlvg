#include "SDL.h"
#include "SDL_syswm.h" // Not sure why this is needed -- perhaps for more complicated use cases.

#include "MLAppController.h"
#include "mlvg.h"
#include "MLSDLUtils.h"

#include "helloMadrona.h"
#include "helloMadronaView.h"

const ml::Vec2 kDefaultGridUnits{ 16, 9 };
const int kDefaultGridUnitSize{ 30 };

void readParameterDescriptions(ParameterDescriptionList& params)
{
    // Controller parameters
    params.push_back( std::make_unique< ParameterDescription >(WithValues{
            { "name", "view_size" },
            { "save_in_controller", true }
    } ) );
}

class HelloMadronaController :
        public AppController
{
public:
    HelloMadronaController(TextFragment appName, const ParameterDescriptionList& pdl) : AppController(appName, pdl) {}
    ~HelloMadronaController() = default;

    void onMessage(Message m)
    {
        // We don't listen to orders
    }
};

int main () {
    bool doneFlag{false};

    // read parameter descriptions into a list
    ParameterDescriptionList pdl;
    readParameterDescriptions(pdl);

    // make controller and get instance number. The Controller
    // creates the ActorRegistry, allowing us to register other Actors.
    HelloMadronaController appController(getAppName(), pdl);
    auto instanceNum = appController.getInstanceNum();

    // make view
    HelloMadronaView appView(getAppName(), instanceNum);

    // if there is no persistent rect, use default
    // we have a few utilities in PlatformView that apps can use to make their own default strategies.
    Vec2 c = PlatformView::getPrimaryMonitorCenter();
    float devScale = PlatformView::getDeviceScaleAtPoint(c);


    // set initial size. This is not a fixed-ratio app, meaning the window sizes
    // freely and the grid unit size remains constant.
    appView.setSizeInGridUnits(kDefaultGridUnits);
    appView.setGridSizeDefault(kDefaultGridUnitSize* devScale);

    // get default rect
    Vec2 defaultSize = kDefaultGridUnits * kDefaultGridUnitSize * devScale;
    Rect boundsRect(0, 0, defaultSize.x(), defaultSize.y());
    Rect defaultRect = alignCenterToPoint(boundsRect, c);

    SDL_Window *window = ml::initSDLWindow(appView, defaultRect, "Hello Madrona");

    if(window)
    {
        // attach app view to window, make UI and resize
        ParentWindowInfo windowInfo = ml::getParentWindowInfo(window);
        appView.createPlatformView(windowInfo.windowPtr, windowInfo.flags);
        appView.startTimersAndActor();

        // watch for window resize events during drag
        ResizingEventWatcherData watcherData{ window, &appView };
        SDL_AddEventWatch(resizingEventWatcher, &watcherData);
        SdlAppResize(&watcherData); // Called within resizingEventWatcher -- redundant? initial state?

        appController.broadcastParams();

        // just vibe
        while(!doneFlag)
        {
            SDLAppLoop(window, &doneFlag);
        }

        // stop doing things and quit
        appView.stopTimersAndActor();
        SDL_Quit();
    }
    return 0;
}

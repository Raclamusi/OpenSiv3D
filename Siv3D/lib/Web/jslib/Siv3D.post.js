(function () {
    const dependencyName = "WebGPU";

    addRunDependency(dependencyName);

    (async function() {
        try {
            const adapter = await navigator.gpu.requestAdapter();
            const device = await adapter.requestDevice();
    
            Module["preinitializedWebGPUDevice"] = device;
        } catch(_) {
            // ignore
        } finally {
            removeRunDependency(dependencyName);
        }
    })();

    if (Module["_emscripten_clear_interval"]) {
        Module["_emscripten_clear_interval"].sig = "vi";
    }

    siv3dRegisterUserAction(() => {
        const ctx = Module["getCurrentAudioContext"]();
        if (ctx.state === "suspended") {
            ctx.resume();
        }
    });

    {
        let keyDownEvent = null;
        let timeoutId = null;
    
        addEventListener("keydown", event => {
            if (!event.isTrusted) {
                return;
            }
            keyDownEvent = event;
        });
    
        addEventListener("keyup", event => {
            if (!event.isTrusted) {
                return;
            }
            const keyUpEvent = event;
            if (keyDownEvent.timeStamp === keyUpEvent.timeStamp) {
                clearTimeout(timeoutId);
                dispatchEvent(keyDownEvent);
                timeoutId = setTimeout(() => {
                    dispatchEvent(keyUpEvent);
                    timeoutId = null;
                }, 100);
            }
        });
    }

    // Workaround for mouseup event not firing when the mouse is released outside the canvas
    {
        let mouseButtonState = 0;
        /** @param {MouseEvent} event */
        const updateMouseButtonState = event => {
            if (!event.isTrusted || event.button < 0 || event.button > 2) {
                return;
            }
            {
                const buttonBit = [1, 4, 2][event.button];
                if (event.type === "mousedown") {
                    mouseButtonState |= buttonBit;
                }
                else if (event.type === "mouseup") {
                    mouseButtonState &= ~buttonBit;
                }
            }
            const unreleasedButtons = mouseButtonState & ~event.buttons;
            for (let button = 0; button <= 2; ++button) {
                const buttonBit = [1, 4, 2][button];
                if (unreleasedButtons & buttonBit) {
                    mouseButtonState &= ~buttonBit;
                    event.target.dispatchEvent(new MouseEvent("mouseup", {
                        button: button,
                        buttons: mouseButtonState,
                        clientX: event.clientX,
                        clientY: event.clientY,
                        screenX: event.screenX,
                        screenY: event.screenY,
                    }));
                }
            }
        };
        const canvas = Module["canvas"];
        canvas.addEventListener("mousedown", updateMouseButtonState);
        canvas.addEventListener("mousemove", updateMouseButtonState);
        canvas.addEventListener("mouseup", updateMouseButtonState);
    }
})();

__ATEXIT__.push(function() {
    if (Module["onRuntimeExit"]) {
        Module["onRuntimeExit"](EXITSTATUS || 0);
    }
});

mergeInto(LibraryManager.library, {
    siv3dSetClipboardText: function(ctext) {
        const text = UTF8ToString(ctext);
        
        siv3dRegisterUserAction(function () {
            navigator.clipboard.writeText(text);
        });
    },
    siv3dSetClipboardText__sig: "vi",
    siv3dSetClipboardText__proxy: "sync",
    siv3dSetClipboardText__deps: [ "$siv3dRegisterUserAction" ],

    $siv3dGetClipboardTextImpl: function(wakeUp) {
        if (!navigator.clipboard.readText) {
            err("Reading clipboard is not allowed in this browser.");
            wakeUp(0);
            return;
        }

        siv3dRegisterUserAction(function () {
            navigator.clipboard.readText()
                .then(function(str) {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                    wakeUp(strPtr);
                })
                .catch(function(_) {
                    wakeUp(0);
                });
        });
    },
    $siv3dGetClipboardTextImpl__deps: [ "$siv3dRegisterUserAction" ],

#if ASYNCIFY
    siv3dGetClipboardText: function() {
        return Asyncify.handleSleep(siv3dGetClipboardTextImpl);
    },
    siv3dGetClipboardText__sig: "iv",
    siv3dGetClipboardText__deps: [ "$siv3dGetClipboardTextImpl", "$Asyncify" ],
#elif PROXY_TO_PTHREAD
    siv3dGetClipboardText: function(ctx) {
        siv3dGetClipboardTextImpl(function () {
            Module["_emscripten_proxy_finish"](ctx);
        });
    },
    siv3dGetClipboardText__sig: "ii",
    siv3dGetClipboardText__deps: [ "$siv3dGetClipboardTextImpl" ],
#else
    siv3dGetClipboardText: function() {
        return 0;
    },
    siv3dGetClipboardText__sig: "iv",
#endif

    siv3dGetClipboardTextAsync: function(callback, promise) {
        siv3dRegisterUserAction(function () {
            if (!navigator.clipboard.readText) {
                err("Reading clipboard is not allowed in this browser.");
                {{{ makeDynCall('vii', 'callback') }}}(0, promise);
                return;
            }

            navigator.clipboard.readText()
            .then(function(str) {
                const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                {{{ makeDynCall('vii', 'callback') }}}(strPtr, promise);
                Module["_free"](strPtr);
            })
            .catch(function (e) {
                {{{ makeDynCall('vii', 'callback') }}}(0, promise);
            });
        });
    },
    siv3dGetClipboardTextAsync__sig: "vii",
    siv3dGetClipboardTextAsync__deps: [ "$siv3dRegisterUserAction" ],

    siv3dSetClipboardImage: function(pngPtr, pngSize) {
        const pngData = new Uint8Array(HEAPU8.buffer, pngPtr, pngSize);
        const pngBlob = new Blob([ pngData ], { type: "image/png" });
        const clipboardItem = new ClipboardItem({ "image/png": pngBlob });

        siv3dRegisterUserAction(function () {
            navigator.clipboard.write([ clipboardItem ]);
        });
    },
    siv3dSetClipboardImage__sig: "vii",
    siv3dSetClipboardImage__proxy: "sync",
    siv3dSetClipboardImage__deps: [ "$siv3dRegisterUserAction" ],

    $siv3dGetClipboardImageImpl: function(wakeUp, returnPtr) {
        if (!navigator.clipboard.read) {
            err("Reading clipboard is not allowed in this browser.");
            wakeUp();
            return;
        }

        siv3dRegisterUserAction(async function () {
            let ptr = 0;
            let size = 0;
            try {
                const items = await navigator.clipboard.read();
                if (items.length > 0 && items[0].types.includes("image/png")) {
                    const blob = await items[0].getType("image/png");
                    const data = new Uint8Array(await blob.arrayBuffer());
                    ptr = Module["_malloc"](data.length);
                    size = data.length;
                    HEAPU8.set(data, ptr);
                }
            }
            catch (_) {}
            HEAPU32[(returnPtr>>2)+0] = ptr;
            HEAPU32[(returnPtr>>2)+1] = size;
            wakeUp();
        });
    },
    $siv3dGetClipboardImageImpl__deps: [ "$siv3dRegisterUserAction" ],

#if ASYNCIFY
    siv3dGetClipboardImage: function(returnPtr) {
        return Asyncify.handleSleep(function (wakeUp) {
            siv3dGetClipboardImageImpl(wakeUp, returnPtr);
        });
    },
    siv3dGetClipboardImage__sig: "vi",
    siv3dGetClipboardImage__deps: [ "$siv3dGetClipboardImageImpl", "$Asyncify" ],
#elif PROXY_TO_PTHREAD
    siv3dGetClipboardImage: function(ctx, returnPtr) {
        siv3dGetClipboardImageImpl(function () {
            Module["_emscripten_proxy_finish"](ctx);
        }, returnPtr);
    },
    siv3dGetClipboardImage__sig: "vii",
    siv3dGetClipboardImage__deps: [ "$siv3dGetClipboardImageImpl" ],
#else
    siv3dGetClipboardImage: function(returnPtr) {
        HEAPU32[(returnPtr>>2)+0] = 0;
        HEAPU32[(returnPtr>>2)+1] = 0;
    },
    siv3dGetClipboardImage__sig: "vi",
#endif
});
mergeInto(LibraryManager.library, {
    $siv3dPendingUserActions: [],

    $siv3dTriggerUserAction: function() {
        if (navigator.userActivation.isActive) {
            for (const func of siv3dPendingUserActions) {
                func();
            }
            siv3dPendingUserActions.splice(0);
        }
    },
    $siv3dTriggerUserAction__deps: [ "$siv3dPendingUserActions" ],

    $siv3dRegisterUserAction: function(func) {
        siv3dPendingUserActions.push(func);
        siv3dTriggerUserAction();
    },
    $siv3dRegisterUserAction__deps: [ "$siv3dPendingUserActions", "$autoResumeAudioContext", "$dynCall" ],

    $siv3dUserActionHookCallBack: function() {
        siv3dTriggerUserAction();
    },
    $siv3dUserActionHookCallBack__deps: [ "$siv3dTriggerUserAction" ],

    $siv3dUserActionTouchEndCallBack: function(e) {
        siv3dTriggerUserAction();
        e.preventDefault();
    },
    $siv3dUserActionTouchEndCallBack__deps: [ "$siv3dTriggerUserAction" ],

    siv3dStartUserActionHook: function() {
        Module["canvas"].addEventListener('touchend', siv3dUserActionTouchEndCallBack);
        Module["canvas"].addEventListener('mousedown', siv3dUserActionHookCallBack);
        window.addEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStartUserActionHook__sig: "v",
    siv3dStartUserActionHook__deps: [ "$siv3dUserActionHookCallBack", "$siv3dUserActionTouchEndCallBack" ],

    siv3dStopUserActionHook: function() {
        Module["canvas"].removeEventListener('touchend', siv3dUserActionTouchEndCallBack);
        Module["canvas"].removeEventListener('mousedown', siv3dUserActionHookCallBack);
        window.removeEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStopUserActionHook__sig: "v",
    siv3dStopUserActionHook__deps: [ "$siv3dUserActionHookCallBack", "$siv3dUserActionTouchEndCallBack" ],

});

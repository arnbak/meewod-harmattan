
function createPageComponentAndPushToStack(file) {
    var pageComponent = Qt.createComponent(file);

    if(pageComponent.status === Component.Ready)
    {
        pageStack.push(pageComponent);
    } else {
        console.log("Error loading pageComponent:", pageComponent.errorString());
    }
    
}

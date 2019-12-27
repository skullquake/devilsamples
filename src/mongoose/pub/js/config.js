/**
 * Created with IntelliJ IDEA.
 * User: karmstrong
 * Date: 12/13/12
 * Time: 9:56 AM
 * To change this template use File | Settings | File Templates.
 */
var dojoConfig = {
    async: 1,
    cacheBust: 1,
    tlmSiblingOfDojo: false,
    isDebug: true,
    packages: [
        { name: "app", location: "../../js" },
        //{ name: "bootstrap", location: "http://localhost/dojobootstrap" }
        { name: "bootstrap", location: "https://raw.github.com/xsokev/Dojo-Bootstrap/v1.3" }
        //{ name: "bootstrap", location: "http://localhost/cdn/libs/bootstrap/" }
        //{ name: "bootstrap", location: "http://localhost/db/js/bootstrap/" }
    ]
};
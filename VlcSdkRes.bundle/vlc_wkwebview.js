
window.velocee_wk = (typeof(window.velocee_wk) !== "undefined")?window.velocee_wk:
    (function() {
     //console.log("velocee_wk called");
     var blacklist = [];
     var whitelist = [];
     var proxyPort = 0;
     var report = [];
     var wl_pload = false;
     function is_match(res, list) {
            var foundMatch = false;
            console.log("check list res:"+res+"\n");
            console.log(list);
            for (var x = 0; x < list.length; x++) {
                var q = list[x];
                console.log("check item:");console.log(q);
                if (q['type'] == 0) {
                    console.log("type:0");
                    if (res.indexOf(q['value']) == 0) {
                        console.log("match:"+q['value']+" ,index:"+res.indexOf(q['value']));
                        foundMatch = true;
                    }
                } else if (q['type'] == 1) {
                    console.log("type 1");
                    var re = new RegExp('/' + q['value'] + '/');
                    if (re.test(res)) {
                        foundMatch = true;
                    }
                } else if (q['type'] == 3) {
                    console.log("type:3")
                    if (res.indexOf(q['value'], res.length - q['value'].length) !== -1) {
                        foundMatch = true;
                    }
                } else if (q['type'] == 2) {
                    console.log("type:2");
                    var ext = res.split('.').pop();
                    console.log("Found ext:"+ext);
                    if (ext == q['value']) {
                        foundMatch = true;
                        console.log("ext match:");
                    }
                } else {
                    console.log('velocee:unknown type');
                }
                //Report pageload for blocked blacklist items
                if ((foundMatch) && (list == blacklist)) {
                    if (q['pageload']) {
                        report.push(res);
                    }
                    return true;
                }
                if ((foundMatch) && (list == whitelist)) {
                    report.push(res);
                    return true;
                }
            }
            //report whitelist only if nothing matched - blocked by whitelist
            if ((!foundMatch) && (list == whitelist) && (wl_pload)) {
                report.push(res);
                return false;
            }
            if ((!foundMatch) && (list == blacklist)) {
                report.push(res);
            }
            return false;
     }
     
     // Check in white black lists and report if needed
     function check_and_report() {
     
     }
     
     function add_to_report(resnames) {
        for (var p = 0; p < resnames.length; p++) {
            var x = document.getElementsByTagName(resnames[p]);
            for (var q = 0; q < x.length; q++) {
                if (x[q].src.length == 0)
                    continue;
                if (is_match(x[q].src, blacklist))
                    continue;
                if ((whitelist.length > 0) && !(is_match(x[q].src, whitelist)))
                    continue;
                report.push(x[q].src);
            }
        }
     }

     function change_proxy(resnames) {
        //console.log("Change Proxy:"+resnames+" length:"+resnames.length);
        for (var p = 0; p < resnames.length; p++) {
            var x = document.getElementsByTagName(resnames[p]);
            for (var q = 0; q < x.length; q++) {
                if (x[q].src.length == 0)
                    continue;
                if (x[q].src.indexOf('http://127.0.0.1') == -1) {
                    if (is_match(x[q].src, blacklist)) {
                        //console.log("item in blacklist:"+x[q].src);
                        continue;
                    }
                    if ((whitelist.length > 0) && !(is_match(x[q].src, whitelist))) {
                        //console.log("item blocked by whitelist"+x[q].src);
                        continue;
                    }
                    if (x[q].src.length > 0) {
                        if (x[q].src[0] == '/' && x[q].src[1] == '/') {
                            x[q].src = 'http://127.0.0.1:'+proxyPort+'?urlr' + (Math.floor(Math.random() * 90000) + 10000) + '=http://' + x[q].src.slice(2);
                        } else {
                            //console.log("changed src");
                            x[q].src = 'http://127.0.0.1:'+proxyPort+'?urlr' + (Math.floor(Math.random() * 90000) + 10000) + '=' + x[q].src;
                            }
                    }
                    if (x[q].dataset.src !== undefined) {
                        if (x[q].dataset.src[0] == '/' && x[q].dataset.src[1] == '/') {
                            x[q].dataset.src = 'http://127.0.0.1:'+proxyPort+'?urlr' + (Math.floor(Math.random() * 90000) + 10000) + '=http://' + x[q].dataset.src.slice(2);
                        } else {
                            x[q].dataset.src = 'http://127.0.0.1:'+proxyPort+'?urlr' + (Math.floor(Math.random() * 90000) + 10000) + '=' + x[q].dataset.src;
                        }
                    }
                }
            }
        }
     }
    document.onreadystatechange = function() {
        if (document.readyState == 'complete') {
            //console.log("send pageload:"+report.length);
            window.webkit.messageHandlers.veloceeHandler.postMessage(JSON.stringify(report));
        }
    };
    var observed_imgs = 0;
    var observer = new MutationObserver(function(mutations) {
        if (observed_imgs != document.images.length)
        {
            observed_imgs = document.images.length;
            change_proxy(['img']);
        }
    });
    observer.observe(document.querySelector('body'), {
        childList: true
    });
    return {
        process: function() {
            //console.log("*** Velocee process()");
            change_proxy(['img']);
            add_to_report(['video', 'script']);
            if (document.readyState == 'complete') {
                window.webkit.messageHandlers.veloceeHandler.postMessage(JSON.stringify(report));
            }
        },
        init: function(_whitelist, _blacklist, _wl_pageload, _proxyPort) {
            //console.log("velocee init start");
            blacklist = _blacklist;
            whitelist = _whitelist;
            wl_pload = _wl_pageload;
            proxyPort = _proxyPort;
            //console.log("velocee init end");
        },
        printVars: function(){
            console.log("port:"+proxyPort);
            console.log("whitelist:"+whitelist);
            console.log("blacklist:"+blacklist);
     
        }
     }
})();
//velocee.process();
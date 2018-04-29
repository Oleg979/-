const getUserById = id => {

    const params = {
        access_token: '29f482149532ce1b3a0682c53158df8fe0190ae1b03ee8fca8553d00f75f263b5e4f0427ba05f6ef2aa9d',
        user_ids: id,
        fields: 'photo_max_orig, status, online',
        v: 'V'
    }

    return $.ajax({
        url: 'https://api.vk.com/method/users.get?' + $.param(params),
        type: 'GET',
        dataType:'JSONP'
    }).promise()

}


Rx.Observable.fromEvent($('input'),'keyup')
    .pluck('target','value')
    .debounceTime(1500)
    .mergeMap(x => Rx.Observable.fromPromise(getUserById(x)))
    .map(x => x.response[0])
    .subscribe(
        x => {
            $('h1').html(`${x.first_name} ${x.last_name} <i>id:${x.uid}</i>`)
            $('h4').html(`${x.online ? 'online' : ''}`)
            $('h3').html(`<i>${x.status}</i>`)
            $('img').attr('src',x.photo_max_orig)
        },
        err => console.log(err),
        () => console.log('completed')
    )

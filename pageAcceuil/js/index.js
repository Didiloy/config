// needed to have the weather
const key = "9ae317666b214f4db7f142935220502";
const topics = ["music", "sport", "tech", "science", "gaming", "food", "entertainment", "world"];

function initView() {
    // Set the date and hour
    let currentDate = new Date();

    let cDay = currentDate.getDate();
    let cMonth = currentDate.getMonth() + 1;
    let cYear = currentDate.getFullYear();
    let formatedDate = "<b>" + cDay + "/" + cMonth + "/" + cYear + "</b>";

    let date_text = document.querySelector('#date-text');
    date_text.innerHTML = formatedDate;

    let time = currentDate.getHours() + ":" + currentDate.getMinutes();
    let hour_text = document.querySelector("#hour-text");
    hour_text.innerHTML = time;

    // set the listener on the search bar
    search_bar = document.querySelector("#search-input");
    search_bar.addEventListener("keydown", function(event) {
        if (event.key === 'Enter') {
            document.location.href = `https://duckduckgo.com/?q=${search_bar.value}`;
            search_bar.value = "";
        }
    });

    // get the DOM elements to display the weather
    let temperature = document.querySelector('#temperature-text');
    let description = document.querySelector('#weather-description-text');
    let image_weather = document.querySelector('#icon-weather');

    //Get the weather
    let linkWeather = (`http://api.weatherapi.com/v1/current.json?key=${key}&q=Nantes&aqi=no&lang=fr`);
    fetch(linkWeather)
        .then(response => {
            return response.json();
        })
        .then(data => {
            // console.log(data);
            temperature.innerHTML = data.current.temp_c + " °C";
            description.innerHTML = data.current.condition.text;
            let link_icon = data.current.condition.icon
            link_icon = "http:" + link_icon;
            image_weather.setAttribute('src', link_icon);
        });

    //get the dom element to display the news
    let image_news = document.querySelector('#image_news');
    let titre_news = document.querySelector('#titre_news');
    let detail_news = document.querySelector('#detail_news');
    let lien_news = document.querySelector('#lien_news');
    //get the news
    var topic = topics[Math.floor(Math.random() * topics.length)]; //get a random topic from the array
    let linkNews = `https://api.newscatcherapi.com/v2/latest_headlines?countries=FR&page_size=1&when=1d&lang=fr&topic=${topic}`;
    fetch(linkNews, {
            method: 'GET',
            headers: {
                'x-api-key': 'S1YG_0S5p46_ZMgXdcBrJ8kS0WTzYAkNb_LLxpuDkK8'
            }
        })
        .then(response => {
            return response.json();
        })
        .then(data => {
            console.log(data);
            image_news.setAttribute('src', data.articles[0].media);
            image_news.setAttribute('width', 300);
            image_news.setAttribute('height', 200);
            titre_news.innerHTML = data.articles[0].title;
            detail_news.innerHTML = data.articles[0].excerpt;
            lien_news.setAttribute('href', data.articles[0].link);
        })

}
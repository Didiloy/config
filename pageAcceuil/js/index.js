// needed to have the weather
const keyWeather = "9ae317666b214f4db7f142935220502";
const unsplashKey = "zYkwd7-nZyTOB4SXH9cuC6bSiEUneNL8yhLMPiDzGD8"
const topics = ["music", "sport", "tech", "science", "gaming", "food", "entertainment", "world"];
const UNSPLASH_BASE_URL = "https://api.unsplash.com/search/photos";

async function initView() {
    // set the listener on the search bar
    search_bar = document.querySelector("#search-input");
    search_bar.addEventListener("keydown", function(event) {
        if (event.key === 'Enter') {
            let query = search_bar.value;
            if (!["'", "/"].includes(query[1])) {
                document.location.href = `https://duckduckgo.com/?q=${query}`;
                search_bar.value = "";
            } else { //handle quick search
                switch (query[0]) {
                    case "y":
                        if (["'"].includes(query[1])) {
                            document.location.href = `https://www.youtube.com/results?search_query=${query.slice(2)}`;
                        } else if (["/"].includes(query[1])) {
                            document.location.href = `https://www.youtube.com/playlist?list=${query.slice(2)}`;
                        }
                        break;
                    case "r":
                        if (["'"].includes(query[1])) {
                            document.location.href = `https://www.reddit.com/search/?q=${query.slice(2)}`;
                        } else if (["/"].includes(query[1])) {
                            document.location.href = `https://www.reddit.com/r/${query.slice(2)}`;
                        }
                        break;

                    default:
                        break;
                }
            }

        }
    });

    getDate();
    await getWeather();
    await getNews();
    setInterval(getDate, 60000); //chaque minutes
    setInterval(getWeather, 3600000); //chaque 1h
}

function getDate() {
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
}

async function getWeather() {
    // get the DOM elements to display the weather
    let temperature = document.querySelector('#temperature-text');
    let description = document.querySelector('#weather-description-text');
    let image_weather = document.querySelector('#icon-weather');

    //Get the weather
    let linkWeather = (`http://api.weatherapi.com/v1/current.json?key=${keyWeather}&q=Nantes&aqi=no&lang=fr`);
    await fetch(linkWeather)
        .then(response => {
            return response.json();
        })
        .then(async data => {
            // console.log(data);
            temperature.innerHTML = data.current.temp_c + " °C";
            description.innerHTML = data.current.condition.text;
            let link_icon = data.current.condition.icon
            link_icon = "http:" + link_icon;
            image_weather.setAttribute('src', link_icon);
            await getWallpaper(data.current.condition.text);
        });
}

async function getNews() {
    //get the dom element to display the news
    let image_news = document.querySelector('#image_news');
    let titre_news = document.querySelector('#titre_news');
    let detail_news = document.querySelector('#detail_news');
    let lien_news = document.querySelector('#lien_news');
    //get the news
    var topic = topics[Math.floor(Math.random() * topics.length)]; //get a random topic from the array
    let linkNews = `https://api.newscatcherapi.com/v2/latest_headlines?countries=FR&page_size=1&when=1d&lang=fr&topic=${topic}`;
    await fetch(linkNews, {
            method: 'GET',
            headers: {
                'x-api-key': 'S1YG_0S5p46_ZMgXdcBrJ8kS0WTzYAkNb_LLxpuDkK8'
            }
        })
        .then(response => {
            return response.json();
        })
        .then(data => {
            // console.log(data);
            image_news.setAttribute('src', data.articles[0].media);
            image_news.setAttribute('width', 300);
            image_news.setAttribute('height', 200);
            titre_news.innerHTML = data.articles[0].title;
            detail_news.innerHTML = data.articles[0].excerpt;
            lien_news.setAttribute('href', data.articles[0].link);
        })

}

async function getWallpaper(keyword) {
    let body = document.querySelector('.body');
    if (keyword.toLowerCase() === 'clair') {
        keyword = 'good weather';
    } else if (keyword.toLowerCase() === 'ensoleillé') {
        keyword = 'summer landscape';
    } else if (keyword.toLowerCase() === 'couvert') {
        keyword = 'cloudy weather';
    }
    fetch(UNSPLASH_BASE_URL + `?client_id=${unsplashKey}&query=${keyword}&per_page=8&orientation=landscape`)
        .then(async(response) => {
            response.json().then((data) => {
                // console.log(data.results);
                let linkNumber = Math.floor(Math.random() * data.results.length);
                try {
                    let linkPicture = data.results[linkNumber].urls.regular;
                    body.backgroundColor = 'none';
                    body.style.backgroundImage = 'url(' + linkPicture + ')';
                    body.style.backgroundSize = 'cover';
                } catch (error) {
                    console.log(error);
                }

            })
        })
}
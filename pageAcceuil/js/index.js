// needed to have the weather
const keyWeather = "9ae317666b214f4db7f142935220502";
const unsplashKey = "zYkwd7-nZyTOB4SXH9cuC6bSiEUneNL8yhLMPiDzGD8";
const UNSPLASH_BASE_URL = "https://api.unsplash.com/photos/random";
const days = [
    "Dimanche",
    "Lundi",
    "Mardi",
    "Mercredi",
    "Jeudi",
    "Vendredi",
    "Samedi",
];
const months = [
    "Janvier",
    "Février",
    "Mars",
    "Avril",
    "Mai",
    "Juin",
    "Juillet",
    "Aout",
    "Septembre",
    "Octobre",
    "Novembre",
    "Décembre",
];

async function initView() {
    // set the listener on the search bar
    search_bar = document.querySelector("#search-input");
    search_bar.focus();
    search_bar.select();
    search_bar.addEventListener("keydown", function(event) {
        if (event.key === "Enter") {
            let query = search_bar.value;
            if (!["'", "/"].includes(query[1])) {
                document.location.href = `https://duckduckgo.com/?q=${query}`;
                search_bar.value = "";
            } else {
                //handle quick search
                switch (query[0]) {
                    case "m":
                        document.location.href = `https://music.youtube.com/search?q=${query.slice(
              2
            )}`;
                        break;
                    case "y":
                        if (["'"].includes(query[1])) {
                            document.location.href = `https://www.youtube.com/results?search_query=${query.slice(
                2
              )}`;
                        } else if (["/"].includes(query[1])) {
                            document.location.href = `https://www.youtube.com/playlist?list=${query.slice(
                2
              )}`;
                        }
                        break;
                    case "r":
                        if (["'"].includes(query[1])) {
                            document.location.href = `https://www.reddit.com/search/?q=${query.slice(
                2
              )}`;
                        } else if (["/"].includes(query[1])) {
                            document.location.href = `https://www.reddit.com/r/${query.slice(
                2
              )}`;
                        }
                        break;
                    case "g":
                        if (["'"].includes(query[1])) {
                            document.location.href = `https://www.google.com/search?q=${query.slice(
                2
              )}`;
                        }

                    default:
                        break;
                }
            }
        }
    });

    getDate();
    await getWeather();
    setInterval(getDate, 60000); //chaque minutes
    setInterval(getWeather, 3600000); //chaque 1h
}

function getDate() {
    // Set the date and hour
    let currentDate = new Date();

    let day = days[currentDate.getDay()];
    let cDay = currentDate.getDate();
    let cMonth = currentDate.getMonth() + 1;
    let cYear = currentDate.getFullYear();
    let formatedDate =
        "<b>" + cDay + " " + months[cMonth - 1] + " " + cYear + "</b>";

    let day_text = document.querySelector("#day");
    day_text.innerHTML = day;
    let date_text = document.querySelector("#date-text");
    date_text.innerHTML = formatedDate;

    let time =
        currentDate.getHours() +
        ":" +
        (currentDate.getMinutes() < 10 ?
            "0" + currentDate.getMinutes() :
            currentDate.getMinutes());
    let hour_text = document.querySelector("#hour-text");
    hour_text.innerHTML = time;
}

async function getWeather() {
    // get the DOM elements to display the weather
    let temperature = document.querySelector("#temperature-text");
    let description = document.querySelector("#weather-description-text");

    //Get the weather
    let linkWeather = `http://api.weatherapi.com/v1/current.json?key=${keyWeather}&q=Poitiers&aqi=no&lang=fr`;
    await fetch(linkWeather)
        .then((response) => {
            return response.json();
        })
        .then(async(data) => {
            // console.log(data);
            temperature.innerHTML = data.current.temp_c + " °C";
            description.innerHTML = data.current.condition.text;
            let link_icon = data.current.condition.icon;
            link_icon = "http:" + link_icon;
            await getWallpaper();
        });
}

async function getWallpaper() {
    let body = document.querySelector(".body");
    fetch(
        UNSPLASH_BASE_URL + `?client_id=${unsplashKey}&orientation=landscape`
    ).then(async(response) => {
        response.json().then((data) => {
            // console.log(data);
            try {
                let linkPicture = data.urls.full;
                body.backgroundColor = "none";
                body.style.backgroundImage = "url(" + linkPicture + ")";
                body.style.backgroundSize = "cover";
            } catch (error) {
                console.log(error);
            }
        });
    });
}
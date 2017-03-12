$(function () {
  var model = {
    imageSources: {
      background: "/images/app/background.png",
      telegram: "/images/app/telegram.png",
      download: "/images/app/download.png",
      samsung: "/images/app/samsung.png"
    }
  };

  var controller = {
    init: function () {
      view.init();
    },
    getImageSources: function () {
      return model.imageSources;
    },
    shareTelegramLink: function () {
      var link = document.createElement('a');
      // TODO: change http://kingofwallpapers.com/image/image-025.jpg to view.$image.attr("src")
      var telegramLink = "https://telegram.me/share/url?url=" +
                         "http://kingofwallpapers.com/image/image-025.jpg" +
                         "&text='سال نو مبارک'";
      link.href = telegramLink;
      link.click();
      link.remove();
    },
    downloadImage: function () {
      // var link = document.createElement('a');
      // link.href = view.$image.attr("src");
      // // TODO: specify a good name for each card in link.download
      // link.download = "download.png";
      // link.click();
      // link.remove();
      window.location.href = "http://localhost:3000" + view.$image.attr("src");
    }
  };

  var view = {
    cacheDom: function () {
      this.$imageSharing = $("#image-sharing");
      this.$telegram = $("#telegram");
      this.$download = $("#download");
      this.$image = $("#image");
      this.$samsungImage = $("#samsung");
    },
    bindEvents: function () {
      this.$telegram.on("click", controller.shareTelegramLink);
      this.$download.on("click", controller.downloadImage);
    },
    init: function () {
      this.cacheDom();
      this.bindEvents();
      this.render();
    },
    render: function () {
      this.$imageSharing.parent().css("background-image", 'url(' + controller.getImageSources().background + ')');
      this.$imageSharing.parent().css("background-size", '100% 100%');
      this.$imageSharing.parent().css("min-width", '100vw');
      this.$imageSharing.parent().css("min-height", '100vh');
      this.$telegram.attr("src", controller.getImageSources().telegram);
      this.$download.attr("src", controller.getImageSources().download);
      this.$samsungImage.attr("src", controller.getImageSources().samsung);
    }
  };

  controller.init();
});

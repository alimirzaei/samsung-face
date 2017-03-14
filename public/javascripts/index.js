$(function () {
  var model = {
    imageSources: {
      background: "/images/app/background.png",
      happyNewYear: "/images/app/happy-new-year.png",
      beAmoo: "/images/app/be-amoo-button.png",
      topLeftCard: "/images/app/chat-card.jpg",
      topRightCard: "/images/app/khros-card.jpg",
      bottomLeftCard: "/images/app/sib-card.jpg",
      bottomRightCard: "/images/app/sabze-card.jpg",
      amooCard: "/images/app/amoo-card.png",
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
    processImage: function () {
      $(this).parent().submit();
    }
  };

  var view = {
    cacheDom: function () {
      this.$happyNewYear = $("#happy-new-year");
      this.$happyNewYearImage = $("#happy-new-year-text");
      this.$beAmooButtonImage = $("#be-amoo");
      this.$topLeftCardImage = $("#top-left-card");
      this.$topRightCardImage = $("#top-right-card");
      this.$bottomLeftCardImage = $("#bottom-left-card");
      this.$bottomRightCardImage = $("#bottom-right-card");
      this.$amooCardImage = $("#amoo-card");
      this.$samsungImage = $("#samsung");
      this.$fileInput = $("#file-input");
    },
    bindEvents: function () {
      this.$topLeftCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/app/1";
      });
      this.$topRightCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/app/2";
      });
      this.$bottomLeftCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/app/3";
      });
      this.$bottomRightCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/app/4";
      });

      this.$amooCardImage.on("click", function () {
        view.$fileInput.click();
      });
      this.$beAmooButtonImage.on("click", function () {
        view.$fileInput.click();
      });

      this.$fileInput.on("change", controller.processImage);


    },
    init: function () {
      this.cacheDom();
      this.bindEvents();
      this.render();
    },
    render: function () {
      this.$happyNewYear.parent().css("background-image", 'url(' + controller.getImageSources().background + ')');
      this.$happyNewYear.parent().css("background-size", '100% 100%');
      this.$happyNewYear.parent().css("min-width", '100vw');
      this.$happyNewYear.parent().css("min-height", '100vh');
      // this.$happyNewYearImage.attr("src", controller.getImageSources().happyNewYear);
      this.$beAmooButtonImage.attr("src", controller.getImageSources().beAmoo);
      this.$topLeftCardImage.attr("src", controller.getImageSources().topLeftCard);
      this.$topRightCardImage.attr("src", controller.getImageSources().topRightCard);
      this.$bottomLeftCardImage.attr("src", controller.getImageSources().bottomLeftCard);
      this.$bottomRightCardImage.attr("src", controller.getImageSources().bottomRightCard);
      this.$amooCardImage.attr("src", controller.getImageSources().amooCard);
      this.$samsungImage.attr("src", controller.getImageSources().samsung);
    }
  };

  controller.init();
});

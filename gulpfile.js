var gulp        = require('gulp');
var browserSync = require('browser-sync').create();
var sass        = require('gulp-sass');

// Static Server + watching scss/html files
gulp.task('serve', ['sass'], function() {

    browserSync.init({
        proxy: "localhost:3000"
    });

    gulp.watch("public/scss/*.scss", ['sass']);
    gulp.watch("public/*.html").on('change', browserSync.reload);
    gulp.watch("public/javascripts/*.js").on('change', browserSync.reload);
    gulp.watch("views/*.hjs").on('change', browserSync.reload);
});

// Compile sass into CSS & auto-inject into browsers
gulp.task('sass', function() {
    return gulp.src("public/scss/*.scss")
        .pipe(sass())
        .pipe(gulp.dest("public/stylesheets"))
        .pipe(browserSync.stream());
});

gulp.task('default', ['serve']);

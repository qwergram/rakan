# Generated by Django 3.0.6 on 2020-05-26 22:09

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('api', '0005_auto_20200526_2012'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='job',
            name='status',
        ),
        migrations.AddField(
            model_name='job',
            name='generatedMaps',
            field=models.ManyToManyField(blank=True, to='api.GeneratedMap'),
        ),
        migrations.AddField(
            model_name='job',
            name='state',
            field=models.ForeignKey(default=1, on_delete=django.db.models.deletion.CASCADE, to='api.State'),
            preserve_default=False,
        ),
    ]

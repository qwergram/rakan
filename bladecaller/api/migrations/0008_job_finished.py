# Generated by Django 3.0.6 on 2020-05-26 22:57

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('api', '0007_auto_20200526_2248'),
    ]

    operations = [
        migrations.AddField(
            model_name='job',
            name='finished',
            field=models.BooleanField(default=False),
        ),
    ]
